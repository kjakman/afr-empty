<?php
namespace AFR;

class View {
    protected $app;    
    protected $elements;    
    protected $scope;
    protected $name; /** e.g. product/view - generally corresponds to controller/action */
    protected $template; /** product/view.html or product/view.tpl or components/_some-template.html */ 
    protected $filename; /** /approot/view/product/view.html, /docroot/view/product/view.html or /docroot/smarty/template/product/view.html */
    
    /** 
      *  @param string $template
      *  @param bool $component
      *
      *  Only used for top level templates     
      */
    public function __construct($app, $name)
    {
        $this->app = $app;
        $logger = $app->logger;
        $config = $app->config;
        $docroot = $config->doc_root;        
        $this->template_dir = $template_dir = "{$docroot}/smarty/templates";
        
        $this->name = $name;
        list($template, $filename) = $this->prepare($name);
        $this->template = $template;
        $this->filename = $filename;
        $logger->debug("View::constructor name:{$name} tpl:{$template} tpldir:{$template_dir} file:{$filename} page: {$app->page_id}");
        
        /** filename only returned if parsing is needed, e.g. not live or missing */
        if($filename) {
            $this->elements = $this->templateElements($app->page_id); /** get page elements. Not needed if live, already in template */
            $logger->debug("View::constructor: element count=".count($elements));
            $this->create($template, $filename);            
        } 
        
    }
    
    /** 
      *  @param string $template
      *  @param bool $component
      *
      *  @return array Relative and fully qualified template path   
      *
      *  if $app->live:
      *    if parsed template already exists, return path
      *  else
      *    if raw template found, parses it and saved to smarty template directory, return path
      * 
      * if $compoenent is true, look in component directory (from {{include}} )
      * 
      */
    private function prepare($name, $component = false)
    {
        $app = $this->app;
        $config = $app->config;
        $logger = $app->logger;
        $docroot = $config->doc_root;
        $approot = $config->app_root;                
        $smarty_dir = $this->template_dir;

        if(!$name) {
          $logger->error("View::prepare missing template name");                      
          return [];
        }

        //$filename = str_replace('.html', '.tpl', $filename); // backward compat        
        $template = strpos($name, '.html') ? $name : "{$name}.html";
        $template = ltrim($template, '/');
        
        /** Live, return already parsed file. Rest is only done for dev/test */
        if($app->live && file_exists("{$smarty_dir}/{$template}")) { // for www, no preparsing, use already parsed smarty template
            return [$template, ""];
        }
        
        /** Below is only done for dev/test */
        $dir = $component ? "views/components" : "views";
        $site_template_file = "{$docroot}/{$dir}/$template";
        $app_template_file = "{$approot}/{$dir}/$template";
        if(file_exists($site_template_file)) {
            $this->local_template = 1;
            $filename = $site_template_file;
        } else if(file_exists($app_template_file)) {
            $this->local_template = 0;
            $filename = $app_template_file;
        } else {
            $logger->debug("View::prepare no {$name} in {$site_template_file} or {$app_template_file}");            
            return []; /** no template throw error */
        }              
        $logger->debug("View::prepare found {$name} in {$template}");            

        if($component && strpos($template, 'components/') === false) {
          $template = "components/{$template}"; // prepend
          $logger->debug("View::prepare prenpend components template={$template}");
        }  
        
        return [$template, $filename];
    }

    /** reads our template from disk, calls parse, writes result to smarty template directory */
    public function create($template, $filename)
    {
        if(!$filename) return '';
        
        $app = $this->app;
        $logger = $app->logger;
        $docroot = $app->config->doc_root;        
        $raw_template = read_file($filename);
        $len = strlen($raw_template);
        $logger->debug("View::create Read $len from {$filename}");
        if(!$len) return '';
        
        $logger->debug("View::create site_id:{$this->app->site_id} page_id:{$this->app->page_id} page id:{$this->app->page->id}");
        
        $parsed_template = $this->parse($raw_template);
        $len = strlen($parsed_template);
        
        if(!$len) die("View::create: parse return 0b");
        
        $smarty_template = "{$docroot}/smarty/templates/$template";
        $path_parts = pathinfo($smarty_template);
        
        $dir = $path_parts['dirname']."/";
        if(!is_dir($dir) && !mkdir($dir, 0775, true)) die("View::create: Failed to create $dir");

        $logger->debug("Writing $len to {$smarty_template}");
        
        if(!write_file($smarty_template, $parsed_template)) die("View::create: Failed to write to {$docroot}/smarty/templates/$template len=".strlen($parsed_template));         
        
        return $template;
    }
    

    /** find page elements in db for this page */
    private function templateElements($page_id) {
        if(!$page_id) return false;
        $app = $this->app;
        
        $elements = [];
        $search = ['site_id' => $app->site_id, 'page_id' => $page_id, 'language' => [$app->language, '*']];
        if($pageElementObjs = find_objects('page_element', $search)) {
            foreach($pageElementObjs as $pageElementObj) {
                $elements[$pageElementObj->name] = $pageElementObj;
                //$template[$pageElementObj->name] = $pageElementObj->content;
            }
        }
        return $elements;
    }
    
    /** parses template from our raw template - replacing page elements */
    private function parse($template)
    {        
        $pattern = '|\{\{\s?(.*?)\s?\}\}|s'; // ungreedy to allow more on one line    
        $output = preg_replace_callback (
            $pattern, 
            function($matches) {
                $match = $matches[1];
                if(!$match) return '';
                if($match[0] == '"' || $match[0] == "'" || $match[0] == "[") { // json?
                    return $this->parseJsonTag($match);
                } else if($match[0] == '$') { // variable
                    return $this->parseVariableTag($match);
                } else { // no match.
                    return ' { '.$match.' } ';
                }
            }, 
            $template);
        return $output;
    }
    
    
    /** from parse_template_variable() - still in use ? */
    private function parseVariableTag($match)
    {         
        $pattern = '#\$(page|site|template|user|scope)\.([a-zA-Z_\-0-9]+)\.?([a-zA-Z_\-0-9]+)?\.?([a-zA-Z_\-0-9]+)?\.?([a-zA-Z_\-0-9]+)?#';
        if(preg_match($pattern, $match, $m)) {
            $var = $m[1];
            $key = $m[2];
            if($var && $key) {
                switch($var) {
                case 'site':
                    $siteObj = $this->app->site;
                    return $siteObj->$key;
                    break;
                case 'page':
                     $pageObj = $this->app->page;
                     return $pageObj->$key;
                    break;
                case 'template':
                    $pageElementArray = $this->elements;
                    $pageElementObj = $pageElementArray[$key];
                    return $pageElementObj->content;
                    
                case 'user':
                    $userObj = $_SESSION['userObj'];
                    return $userObj->$key;
            
                case 'scope':
                    $count = count($m);
                    $scope = $this->app->scope;
                    $i=2;
                    while($i < $count) { // traverse object chain to leaf
                        $key = $m[$i];
                        $result = $scope->$key;
                        $scope = $result;
                        $i++;
                    }
                    if(is_object($result)) {
                        $chain = array_slice($m, 2);
                        $result = implode(".",$chain).' = [object]';
                    }
                    return $result;
                    break;
                default:
                    return '';
                    break;
                }
            }
        }
    }
    
    /** from parse_template_json() */
    private function parseJsonTag($match)
    {        
        $siteObj = $this->app->site;
        $pageObj = $this->app->page;
        $user_id = $this->app->user_id;
        $logger = $this->app->logger;
        
        $json = $match[0] == '[' ? '["'.str_replace('"', '\"', substr($match, 1, -1)).'"]' : "{".$match."}"; // turn back into json array or object
        $json = str_replace("\n", '', $json);
        $data = json_decode($json);

        //dump($data);
        
        if(!$data) {
            return ''; // todo: show error
        }
                
        if(is_array($data) && count($data)) { // this allows simplified tags for page_elements {{[ and ]}}
            $value = $data[0]; // remove [ and ]
            $data = new stdClass;
            
            $rand = hash('adler32', $value);
            $data->name = "pe-$rand";
            $data->type = $type = strip_tags($value) == $value ? "text" : "html"; // if strip_tags == str, text, else html
            $data->value = $value;
            //dump($data);die("Unrecognized json tag");
            
        } else if($name = $data->extend) { // include file to be parsed
            //echo(" found include $filename, calling preparse...<br>");
            unset($data->extend);            
            list($template, $filename) = $this->prepare($name);
            if($template = $this->create($template, $filename)) {
                return "{extends file=\"$template\"}";
            } else {
                if(!$app->live) mydie("View::parseJsonTag: failed to extend {$name}"); /** todo: remove */
                return "<!-- Extend: Failed to find/parse {$template} -->";
            }
        } else if($name = $data->include) { // include file to be parsed
            //echo(" found include $filename, calling preparse...<br>");
            unset($data->include);
            list($template, $filename) = $this->prepare($name, true);
            if($template = $this->create($template, $filename)) {
                $data_str = array2args($data);
                return "{include file=\"{$template}\" {$data_str}}";
            } else {
                if(!$app->live) mydie("View::parseJsonTag: failed to include {$name}"); /** todo: remove */
                return "<!-- Include: Failed to find/parse {$template} -->";
            }
        } else if($subviews = $data->subviews) { // include array of files to be parsed
            //dump($subviews);dump($data);die();
            //echo(" found include $filename, calling preparse...<br>");
            unset($data->include);
            if($prefix = $data->prefix) {
              unset($data->prefix);
            }
            $data_str = array2args($data);  
            $subviews_str = implode(',', $subviews);
            $i = 0;
            foreach($subviews as $subview) {              
              $name = "{$prefix}{$subview}";
              list($template, $filename) = $this->prepare($name, true);
              $logger->info("View::parseJsonTag: creating subview {$template}");
              if(!$i) $first_template = $template;
              if(!$template = $this->create($template, $filename)) {
                  if(!$app->live) mydie("View::parseJsonTag: failed to include subview {$prefix}{$subview}"); /** todo: remove */
              }
              $logger->info("View::parseJsonTag: created subview {$template}");
              $i++;
            }
            $output = "<!-- {$i} Subviews: {$subviews_str} -->";
            $output .= '  {$tpl = $scope.view_template}'.PHP_EOL;
            $output .= '  {$tpl = $scope.view_template|default:"'.$first_template.'"}'.PHP_EOL;  /** include first view by default */
            $output .= '  {include file="$tpl" '.$data_str.'}'.PHP_EOL;
            return $output;
            
        } else {
            //dump($data);die("Unrecognized json tag");
            
        }
        
        $debug = '';
        $name = $data->name;
        
        $elements = $this->elements ?: [];
        
        $dbObj = isset($elements[$name]) ? $elements[$name] : null;
        $element_id = $dbObj->id;

        $logger->debug("View::parseJsonTag: name={$name} id={$element_id} count=".count($elements));
        
        
        //$dbObj = find_object('page_element', []
        $type = $data->type;
        $value = $dbObj ? $dbObj->content : $data->value;
        $options = $data->options ? (array) $data->options : array();
        
        $keys = array('class', 'style', 'js', 'alt'); /** todo, add more here that's relevant for tag */
        foreach($keys as $key) {
            if(isset($data->$key)) $options[$key] = $data->$key;
        }
        
        $store = true;
        //echo("name=$name type=$type value=$value edit=$auth_edit<br>");
        $field = 'content';
        $media_options = array();
        if(in_array($type, array('image','audio','video', 'media'))) {
            $media_options = media_options(array('resize' => 1, 'allow_multiple' => false));
            $field = 'media';
            $media_id = $dbObj->media;
            if(!$media_id && $element_id) { /** add to database so we can edit later */
                $page_id = $dbObj->page_id ?: $pageObj->id;
                $mediaData = array();
                $mediaData['name'] = $name;
                $mediaData['path'] = "/user/page/$page_id/$element_id/$type/";
                $mediaData['parent_type'] = 'page_element';
                $mediaData['parent_id'] = $element_id;
                $mediaData['parent_field'] = 'media';
                $mediaData['user_id'] = $u_id;            
                $mediaData['url'] = is_url($value) ? $value : site_full_url($siteObj)."/".ltrim($value, '/');
                $mediaData['resize'] = $data->resize ?: 800; /** resize to max 800px longest side ? */
                if(1) {            
                    list($media_id, $media_errors) = add_object('media', $mediaData);
                    if($media_id) update_object('page_element', array('media' => $media_id), $dbObj->id);
                    else if($media_errors) $debug = print_errors($media_errors);
                }
            }
            $media_src = $media_id ? print_media($media_id, array('source_only' => true)) : $value;
            //$media_src = $media_id ? print_media($media_id, array('source_only' => true)) : $value;
        }
    
        $obj_type = 'page_element'; // default    for page_element
        $edit_id = $dbObj->id; // default for page_element
        
        /**
        $this->logger->lo
        if($name[0] == '$') { // this is from page_content, not page_element
            $obj_type = 'page_content';
            $field = ltrim($name, '$');
            $edit_id = $pageObj->content_id;
            $store = false; // don't store, this is from $pageContentObj
            $class_def = get_class_def($obj_type, false);
            
            if($attr = $class_def->fields[$field]) {
                //dump($class_def);
                $type = $attr[ATT_TYPE];
                if($type == 'str') $type = 'text';
                $value = $pageObj->$field;
            } else {
                $output = "<!-- Parse error - Unknown page_content variable '$field': $json -->";
                return $output;            
            }
        }
        */
        
        switch($type) {                                     
        case 'text':
            $output = $value;
            break;
        case 'html':
            $output = $value;
            break;
        case 'image':
            //$output = $media_src;
            $output = html_image($media_src, $options['alt'], $options);
            $media_options['allowed_types'] = 'image';
            break;
        case 'video':
            $output = html5_video($media_src, $options['alt'], $options);
            $media_options['allowed_types'] = 'video';
            break;
        case 'audio':
            $output = html5_audio($media_src, $options['alt'], $options);
            $media_options['allowed_types'] = 'audio';
            break;
        case 'media':
            $output = html_image($value, $options['alt'], $options);
            break;
        case 'variable':
            $store = false;
            $output = '<!--$'.$name.'-->'; "Variable $json";
            break;
        default:
            $store = false;
            $output = "<!-- Parse error - Unsupported type '$type': $json -->";
            break;
        }
    
        //echo("Name=$name type=$type field=$field store=$store<br>");
    
        //if($store && !$pageElementArray[$name]) { // store in database if doesn't exist
        if($store && !$element_id) { // store in database if doesn't exist
            if($this->app->page_id) {
                $db_data = array();
                $db_data['site_id'] = $this->app->site_id;
                $db_data['page_id'] = $this->app->page_id;
                $db_data['language'] = $this->app->language;
                $db_data['name'] = $name;
                $db_data['type'] = $type;
                $db_data['content'] = $value;
                $db_data['options'] = $options ? json_encode($options) : '';
                list($id, $errors) = add_object('page_element', $db_data);
                if($errors) { /** todo: exception */
                    dump($db_data);
                    dump($errors);
                    mydie();
                }
                $edit_id = $id;
            } else {
                $logger->error("View::parseJsonTag: cannot store element - no page ID");
            }
        }                                 
        
        if($_SESSION['__edit_mode']) {
            $edit_class = $auth_edit ? '__edit ' : ''; 
            $media_button = '';
            if(in_array($type, array('image','audio','video', 'media'))) {
                $media_button = html_div(html_image("/images/icons/".$type.".png", 'edit'), 'ie_edit_link');
                $safe_name = url_safe($name);
                $page_id = $pageObj->id; // name might change, so use ID
                
                $upload_options = array();
                $upload_options['path'] = "/user/page/$page_id/$safe_name/"; 
                $upload_options['allow_multiple'] = false;
                
                $resize = $data->resize;
                if($media_id) {
                    $output = '{$options = ["resize" => "'.$resize.'"]}'.PHP_EOL;
                    $output .= '{$json = $options|@json_encode}'.PHP_EOL;
                    $output .= '{"media"|uploader:'.$media_id.':"$json"}'.PHP_EOL;
                } else {
                    $output = "parse_template_json: No media_id for $type $name (try reload)";
                }            
                return $output;
                
            } else if(0 && $type == 'html') {
                return "{\"$element_id\"|editor:\"full\"}";
            }
            $id = site_edit_id($siteObj, $pageObj, $auth_edit, $obj_type, $field, $edit_id, array('type' => $type));
            $edit_options = array('id' => $id);
            
            if($media_options) {
                $class_options->$field = array(ATT_OPTIONS => $media_options); // override options of field content
            }
            
            if(!strlen($output)) $output = "-- empty {$name} --";
            $output = html_div($output, '__edit', $edit_options);
        }
        return $output.$debug;
    }
    
    /** 
        render
        from smarty_parse_template()
    */
    
    public function render()
    {
        $template = $this->template;
        $app = $this->app;
        $scope = $app->scope;
        $header = $app->header;        
        $smarty_dir = $this->template_dir;
        $logger = $app->logger;
        $config = $app->config;
        $docroot = $config->doc_root;        
        $userObj = $app->user;
        $siteObj = $app->site;
        $pageObj = $app->page;
        
        $logger->debug("View::render tpl:{$template} file:{$filename} ");
        
        
        if(!$template) {
            echo("<h3>oops</h3>No template for {$template}");
            return;
            mydie("View::render: missing filename"); /** todo: exception */ 
        }
        $filename = "{$smarty_dir}/$template";        
        if(!is_file($filename)) {
            echo("<h3>oops</h3>Template file {$filename} not found");
            return;
            mydie("View::render: missing filename"); /** todo: exception */ 
        }
        
        /** todo: get rid of global + session, use app */
        global $__LANGUAGE, $__LANGUAGES, $__USER, $__USER_LEVEL, $__USER_ID, $__PATH_VAR,$__EDIT_MODE, $__CLIENT_ID;
        global $u_id, $u_level, $__header;

        $global = $_SESSION['global_scope'] ?: array();

        $logger->debug("View::render user: {$userObj->id} level: {$userObj->user_level}");
            
        if (!class_exists('Smarty')) require_once('Smarty/Smarty.class.php');        

        //$root = $options['root']; // top level page template? - not in use
        //$main = $options['main']; // main template (content)
        
        
        
        $query_string = get_query_string();
        $this_path = this_path();
        
        if($query_string) $query_string = "?$query_string"; // so we can append it to URLs in template
    
        $auth_edit = $_SESSION['auth_edit'];
        
        if(is_array($options)) foreach($options as $k => $v) $scope->$k = $v;
        $scopeAr = is_array($scope) ? $scope : obj2array($scope, true); // recursive
        $globalAr = obj2array($global);
            
        $smarty = new \Smarty();
    
        if(isset($_GET['cache']) && !$_GET['cache']) $smarty->clearAllCache();
    
        $globals = array('u_id' => $u_id, 'u_level' => $u_level);
        
        $smarty->setTemplateDir($docroot.'/smarty/templates');
        $smarty->setCompileDir($docroot.'/smarty/templates_c');
        $smarty->setCacheDir($docroot.'/smarty/cache');
        $smarty->setConfigDir($docroot.'/smarty/configs');
    
        // custom modifiers                                             
        $smarty->registerPlugin('modifier', 'currency', 'currency2html');
        $smarty->registerPlugin('modifier', 'media', 'print_media');
        $smarty->registerPlugin('modifier', 'photo', 'get_media_source');
        $smarty->registerPlugin('modifier', 'photos', 'get_media_sources');
        $smarty->registerPlugin('modifier', 'default', 'return_if_empty');
        $smarty->registerPlugin('modifier', 'date', 'sql2human');
        $smarty->registerPlugin('modifier', 'datetime', 'sql2human_datetime');
        $smarty->registerPlugin('modifier', 'daterange', 'print_time_range');
        $smarty->registerPlugin('modifier', 'add_day', 'add_day');
        $smarty->registerPlugin('modifier', 'strip_time', 'strip_time');
        $smarty->registerPlugin('modifier', 'price', 'formatFloat');
    
        $smarty->registerPlugin('modifier', 'name', 'get_name_string');
        $smarty->registerPlugin('modifier', 'address', 'get_address_string');
        $smarty->registerPlugin('modifier', 'display_name', 'user_display_name');
        $smarty->registerPlugin('modifier', 'displayname', 'user_display_name');
        $smarty->registerPlugin('modifier', 'username', 'user_display_name');
        $smarty->registerPlugin('modifier', 'userphoto', 'user_photo');
        $smarty->registerPlugin('modifier', 'media_list', 'print_media_list');
        $smarty->registerPlugin('modifier', 'fullname', 'get_user_name');
        $smarty->registerPlugin('modifier', 'full_name', 'get_user_name');
        $smarty->registerPlugin('modifier', 'get_user', 'get_user');
        $smarty->registerPlugin('modifier', 'markup', 'txt2html');
        $smarty->registerPlugin('modifier', 'city', 'cityname');
    
        $smarty->registerPlugin('modifier', 'object_key', 'get_object_key');
        $smarty->registerPlugin('modifier', 'object_table', 'get_object_table');
    
        $smarty->registerPlugin('modifier', 'get', 'smarty_get_object');
        $smarty->registerPlugin('modifier', 'find', 'smarty_find_object');
        $smarty->registerPlugin('modifier', 'find_all', 'smarty_find_objects');
        $smarty->registerPlugin('modifier', 'count_objects', 'count_objects');
        
        $smarty->registerPlugin('modifier', 'period_diff', 'period_diff');
        $smarty->registerPlugin('modifier', 'elapsed', 'time_elapsed_human');
        $smarty->registerPlugin('modifier', 'print_array', 'print_array_assoc');
        $smarty->registerPlugin('modifier', 'flag', 'html_flag');
        $smarty->registerPlugin('modifier', 'tooltip', 'html_tooltip');
        $smarty->registerPlugin('modifier', 'checkmark', 'html_checkmark');
        $smarty->registerPlugin('modifier', 'pagination', 'html_pagination');
        $smarty->registerPlugin('modifier', 'object_select', 'object_select');
        $smarty->registerPlugin('modifier', 'myhash', 'myhash');
        $smarty->registerPlugin('modifier', 'alert', 'print_alert');
        $smarty->registerPlugin('modifier', 'translate', 'smarty_translate');
        $smarty->registerPlugin('modifier', 'transplace', 'smarty_transplace');
        $smarty->registerPlugin('modifier', 'permissions', 'permissions_print');
        $smarty->registerPlugin('modifier', 'permissions_edit', 'permissions_edit');
        
        $smarty->registerPlugin('modifier', 'slugify', 'slugify');
        $smarty->registerPlugin('modifier', 'property_geolink', 'smarty_property_geolink');
        $smarty->registerPlugin('modifier', 'property_link', 'smarty_property_link');
        $smarty->registerPlugin('modifier', 'public_link', 'public_link');
    
        $smarty->registerPlugin('modifier', 'plural', 'plural');
        $smarty->registerPlugin('modifier', 'trans', 'phrase');
    
        
        /** Utilities */
        $smarty->registerPlugin('modifier', 'array_remove', 'array_remove');
        $smarty->registerPlugin('modifier', 'array_remove_key', 'array_remove_key');
        $smarty->registerPlugin('modifier', 'obj2array', 'obj2array');
        $smarty->registerPlugin('modifier', 'any2array', 'any2array');
        $smarty->registerPlugin('modifier', 'array2obj', 'array2obj');
        $smarty->registerPlugin('modifier', 'array2list', 'array2list');
    
        /** HTML, TEXT */    
        $smarty->registerPlugin('modifier', 'table', 'html_table');
        $smarty->registerPlugin('modifier', 'anchor', 'html_link');
        $smarty->registerPlugin('modifier', 'nl2br', 'nl2br');
        $smarty->registerPlugin('modifier', 'hide_false', 'hide_false');
        $smarty->registerPlugin('modifier', 'yes_no', 'html_yes_no');
        $smarty->registerPlugin('modifier', 'truncate_html', 'truncate_html');
        $smarty->registerPlugin('modifier', 'strip_style', 'strip_style');
        $smarty->registerPlugin('modifier', 'strip_attribute', 'strip_attribute');
        $smarty->registerPlugin('modifier', 'script', 'html_script');
        $smarty->registerPlugin('modifier', 'style', 'html_style_tag');
    
        
        /** query, path */    
        $smarty->registerPlugin('modifier', 'query', 'build_query_string');
        $smarty->registerPlugin('modifier', 'strip_query', 'strip_query_string');
        $smarty->registerPlugin('modifier', 'link', 'page_link');
        $smarty->registerPlugin('modifier', 'page', 'smarty_page_content');
        $smarty->registerPlugin('modifier', 'get_page', 'smarty_get_page');
        $smarty->registerPlugin('modifier', 'site_url', 'site_url');
        $smarty->registerPlugin('modifier', 'print_link', 'print_page_link');
        $smarty->registerPlugin('modifier', 'error', 'print_errors');
        $smarty->registerPlugin('modifier', 'message', 'print_messages');
        $smarty->registerPlugin('modifier', 'find_page', 'print_page_link');
        $smarty->registerPlugin('modifier', 'parent_path', 'parent_path');
        $smarty->registerPlugin('modifier', 'slug', 'slug');
    
        $smarty->registerPlugin('modifier', 'add_query_var', 'add_query_var');
        $smarty->registerPlugin('modifier', 'remove_query_var', 'remove_query_var');
        $smarty->registerPlugin('modifier', 'replace_query_var', 'replace_query_var');
    
        $smarty->registerPlugin('modifier', 'address_data', 'get_address_data');
    
        /** replace all with templates 
        $smarty->registerPlugin('modifier', 'address_details', 'address_details');
        $smarty->registerPlugin('modifier', 'invoice_details', 'invoice_details');
        $smarty->registerPlugin('modifier', 'invoice_payments', 'print_invoice_payments');
        $smarty->registerPlugin('modifier', 'booking_payments', 'print_booking_payments');    
        $smarty->registerPlugin('modifier', 'arrival_details', 'arrival_details');
        $smarty->registerPlugin('modifier', 'invoice', 'print_invoice');
        */
    
        $smarty->registerPlugin('modifier', 'lineitems', 'get_lineitems');
        
        /** Reservation site specific */
        $smarty->registerPlugin('modifier', 'guest_name', 'reservation_guest_name');    
        /** End Reservation site specific */
    
        /** page edit */
        $smarty->registerPlugin('modifier', 'uploader', 'smarty_uploader');
        $smarty->registerPlugin('modifier', 'media_uploader', 'smarty_media_uploader');
        $smarty->registerPlugin('modifier', 'object_uploader', 'object_media_uploader');
        $smarty->registerPlugin('modifier', 'editor', 'smarty_editor');
        $smarty->registerPlugin('modifier', 'editable', 'smarty_editable');
        
        /** page edit */
        $smarty->registerPlugin('modifier', 'file_icon', 'file_icon');
        $smarty->registerPlugin('modifier', 'file_size', 'filesize');
        $smarty->registerPlugin('modifier', 'file_extension', 'file_extension');
        $smarty->registerPlugin('modifier', 'file_name', 'file_name');
        $smarty->registerPlugin('modifier', 'file_path', 'file_path');
        $smarty->registerPlugin('modifier', 'bytes2human', 'bytes2human');
        
        /** Gallery / Art */
        
        $smarty->registerPlugin('modifier', 'collection_photo', 'collection_title_image');
        $smarty->registerPlugin('modifier', 'folder_photo', 'folder_title_image');
        
        /** Rating */
        $smarty->registerPlugin('modifier', 'stars', 'star_rating');
        $smarty->registerPlugin('modifier', 'rating', 'star_rating');
    
        // smarty functions
        $smarty->registerPlugin('function', 'editable', 'smarty_edit');
        
        $smarty->assign('template_dir', $template_dir);
        $smarty->assign('config', $_SESSION['config'] ?: []);
        
        //$smarty->assign('query_string', get_query_string()); // $_SERVER['QUERY_STRING'] doesn't work as expected due to mod rewrite
        
        foreach($globals as $key => $val) $smarty->assign($key, $value);
        $smarty->assign('today', today());
        $smarty->assign('now', now());
        $smarty->assign('time', time());
        $smarty->assign('live', $_SESSION['live']);
        $smarty->assign('deployment', $_SESSION['deployment']);
        if($userObj->timezone) $smarty->assign('usertime', date());
        
        //$smarty->assign('sites', $_SESSION['client_sites']);
        //$smarty->assign('legal_entities', $_SESSION['client_legal_entities']);
        
        
        $smarty->assign('client_ip', client_ip());
        $smarty->assign('auth_edit', $auth_edit);
        $smarty->assign('edit_mode', $__EDIT_MODE);
        $smarty->assign('client_id', $__CLIENT_ID);
        $smarty->assign('site', (array) $siteObj);
        $smarty->assign('user', (array) $userObj);
        $smarty->assign('page', (array) $pageObj);
        $smarty->assign('page_template', $pageObj->template);
        $smarty->assign('page_controller', $pageObj->controller);
        $smarty->assign('lang', $__LANGUAGE);
        $smarty->assign('language', $__LANGUAGE);
        $smarty->assign('languages', $__LANGUAGES);
        $smarty->assign('root_user', $_SESSION['root_user']);
        $smarty->assign('scope', $scopeAr);
        $smarty->assign('global', $globalAr);
        $smarty->assign('get', $_GET); 
        $smarty->assign('template', $template);     
        $smarty->assign('query_string', $query_string);
        $smarty->assign('doc_root', docroot(false)); // no trailing slash
        $smarty->assign('app_root', approot(false)); // no trailing slash
        $smarty->assign('this_path', this_path());
        $smarty->assign('path_var', $__PATH_VAR);
        $smarty->assign('full_path', full_path());
        $smarty->assign('this_url', remove_query_var(this_url(), 'act'));
        $smarty->assign('site_url', rtrim(site_full_url($siteObj), '/')); // no trailing slash
        $smarty->assign('aff_id', $_SESSION['_aid']);
        $smarty->assign('server', $_SERVER);
        $smarty->assign('header', $header);

        $smarty->assign('dump', smarty_dump);
    
        $logger->debug("View::render fetching {$smarty_dir}/{$template}");
        
        try {                                
            $output = $smarty->fetch("{$smarty_dir}/{$template}");
        }
            catch (Exception $e) {
            $smarty_error = $e->getMessage();
            $scope->error = htmlentities($smarty_error);
            $output = "Cannot parse {$smarty_dir}/{$template}:<br><br>{$smarty_error}";
        }

        return $output;
    
        /**
        if($_SESSION['__edit_mode']) {
            $full_filename = docroot().'/pages/'.$filename;
            if(is_file($full_filename) && is_writeable($full_filename)) {
                $output .= '<a class="btn btn-success __edit_template __edit_link" data-template="'.$full_filename.'" href="#"><i class="fa fa-code"></i> Edit Template '.$filename.'</a>';
            } else {
                //$output .= '<a class="btn btn-success __edit_template __edit_link" data-template="'.$full_filename.'" href="#"><i class="fa fa-code"></i> NOT Edit Template '.$filename." full=$full_filename exists=".is_file($full_filename)." writable=".is_writeable($full_filename).'</a>';
            }
        }
    
        //$output .= print_alert($filename, "message");
        
        if($main) { // only do this once
            if(!$_SESSION['live'] && $scope->debug) $output .= print_alert("Debug: ".$scope->debug, "info");
            if($message = $scope->message ?: $scope->messages) $output .= print_alert($message, "message");
            if($warning = $scope->warning ?: $scope->warnings) $output .= print_alert($warning, "warning");
            if($error = $scope->error ?: $scope->errors) {
                if(1) { 
                    //$output .= form_text('foo', $template);
                    $output .= print_alert($error, "error");
                }
            }
        }
        */
        
        
        
    }
    
}

    