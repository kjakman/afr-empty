<?php

/** still in use 2017, but probably shouldn't be */

function site_data_directory($siteObj_or_id) {
  $siteObj = any2obj('site', $siteObj_or_id);
  $site_shortname = url_safe($siteObj->shortname);
  return $_SESSION['live'] ? "/web/data/$site_shortname/" : "/web/data-dev/$site_shortname/";
}


// takes path parts (from set_env), return page if found
function path2page($siteObj, $path_parts, $options = array()) {
  $debug = $options['debug'];
  $pageObj = null;
  $path_var = '';
  $this_path = count($path_parts) ? '/'.implode('/', $path_parts).'/' : '/';
  $full_path = this_path();
  if(count($path_parts) > 1 ) {
    $last_part = array_pop($path_parts);
    $this_path_min1 = '/'.implode('/', $path_parts).'/';
  } else {
    $last_part = array_pop($path_parts);
    $this_path_min1 = '';
  }
  if($debug) {
    print_log("Looking for ".dump($path_parts, true), 'set_env', LOG_LEVEL_TEST);
    print_log("This path= $this_path", 'set_env', LOG_LEVEL_TEST);
  }

  if($this_path == '/' && $script_lang && ($pageObj = site_home_page($siteObj, $script_lang))) { // special case for home page    
    if($debug) print_log("Ok 1", 'set_env', LOG_LEVEL_TEST);
  } elseif($pageObj = site_find_page($siteObj, $this_path)) {    
    if($debug) print_log("Ok 2", 'set_env', LOG_LEVEL_TEST);
  } elseif($this_path_min1 && ($pageObj = site_find_page($siteObj, $this_path_min1))) { // maybe last path part is a property name or other variable?
    $path_var = $_SESSION['path_var'] = $last_part;
    if($debug) print_log("Ok 3", 'set_env', LOG_LEVEL_TEST);
  }
  return array($pageObj, $path_var);
}


function site_find($domain) {
  $siteObj =  find_object('site', array('domain' => $domain));
  return $siteObj;
}


// prints content of a page
// called directly from controller (index.php), populates pageElements->content
function site_content($siteObj, $pageObj, $options = []) {
  global $__header, $u_level, $u_id;
  $auth_edit = $options['can_edit'] || $options['auth_edit'] || ($u_id && $u_level >= USER_LEVEL_STAFF);
  
  // check for html template on file in /docroot/pages/
  // parsed and populated by page_element objects in DB
  $edit_mode = $_GET['__edit_mode'] == 1;
  if($edit_mode && !trim(strip_tags($pageObj->content))) $pageObj->content = "[Empty content]";

  // check for HTTP status errors
  if(isset($pageObj->http_code) && $pageObj->http_code >= 300) {
    if($pageObj->http_status) header($pageObj->http_status);
    if($pageObj->http_error) header($pageObj->http_error);
    $pageObj->scope->error = $pageObj->http_error;
    $pageObj->template = $pageObj->http_template ?: $pageObj->http_code;
  }
  
  // use blank.html if missing
  // if(!$pageObj->template && $pageObj->page_type == 0) $pageObj->template = $siteObj->default_template ?: 'blank';
  
  $options['main'] = 1; // print warnings/errors only here, not in header/footer etc
  if($template = site_page_template($siteObj, $pageObj, $options)) return $template;

  return $auth_edit ? print_alert("Missing template for {$pageObj->name} ({$pageObj->id})", 'error') : '';
}

/** end still in use 2017 */

function site_html_document($siteObj, $pageObj, $options=NULL) {  
  global $xhtml;
  global $u_level;
  $user_level = $u_level ?: 0;
  $page_level = $pageObj->user_level ?: 0; 
  if($page_level && !$user_level) {
    if($_GET['_new'] == "register") {
      unset($_GET['_new']);
      $login_page = site_page_link($siteObj, PAGE_REGISTER);      
    } else {
      $login_page = site_page_link($siteObj, PAGE_LOGIN);
    }
    $this_url = $_SERVER['REQUEST_URI'];
    $url = "$login_page?ref=".urlencode($this_url);
    if($aid = $_GET['_aid']) $url ="&_aid=$aid";
    //."&ref_name=$pageObj->name"
    //die("page=$page_level u=$user_level redirecting to $url");
    redirect($url);
  }
  if($page_level > $user_level) return "Not authorized (page level > user level)";
  //dump($options);
  $lang = $_SESSION['lang'];
  $output = '<!doctype html>
<!--[if lt IE 7]> <html class="no-js lt-ie9 lt-ie8 lt-ie7" lang="en"> <![endif]-->
<!--[if IE 7]>    <html class="no-js lt-ie9 lt-ie8" lang="en"> <![endif]-->
<!--[if IE 8]>    <html class="no-js lt-ie9" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js" lang="'.$lang.'"> <!--<![endif]-->
';
  $output .= site_head($siteObj, $pageObj, $options);
  $output .= site_body($siteObj, $pageObj, $options);  
  $output .= "
</html>
";
  return $output;

}


//function site_body($siteObj, $pageObj, $can_edit=false, $pageElements='', $html='') {
function site_body($siteObj, $pageObj, $options=NULL) {
  global $xhtml;
  global $__header;
  global $u;
  global $u_id;

  $can_edit = $auth_edit = $options['can_edit'];
  $html     = $options['html'];
  $pageElements = $options['page_elements'] ?: array();
  $framework = $pageObj->framework ?: $siteObj->framework;
  $bootstrap = $_SESSION['bootstrap'] = in_array($framework, array('bootstrap', 'bootstrap-sass'));
  $google_tag_manager = $siteObj->google_tag_id ? google_tag_manager($siteObj->google_tag_id ) : "";

  // onload
  $__header['onload'] .= '';
  
  if($can_edit) {
    $div = $_GET['css_edit'];    
    if($layout_edit) {
      $hide_body = true;
      $db_divs_json = json_encode(find_objects('layout_div'));    
      $data = array('site_id' => $siteObj->id, 'parent_type' => 'site_page', 'parent_id' => $pageObj->id, 'user_id' => $u_id);
      $data_json = json_encode($data);    
      $html = html_h2("Edit layout", 'pad').html_div('The layout div', '', array('id' => 'page_layout'));
      $__header['onload'] .= "page_layout_handler('page_layout', ".$db_divs_json.", ".$data_json.");";
    } else {
      ///$__header['onload'] .= site_edit_js();
    }
  }
  
  if(!$hide_body) $html = site_html($siteObj, $pageObj, $options).$html;
  $onload = $__header['onload'];
  $end_scripts = $__header['end_scripts'];
  $scripts_html = '';
  
  if($onload && !$_SESSION['combine_and_minify']) { // don't do this if we're compressing
    $scripts_html .= html_script_inline('
    $(document).ready(function() {
'.$onload.'        
    });
');
  } else {
    if($_SESSION['combine_and_minify'] && $_SESSION['async'] && count($end_scripts)) {
      $scripts_html .= "<script type='text/javascript'>jQl.loadjQdep('".$end_scripts[0]."');</script>\n"; // should just be one (onload)
      $end_scripts = array();
    } else {
      $scripts_html .= $__header['end_scripts_html'];
    }
  }
  foreach($end_scripts as $script) $scripts_html .= "  ".html_script($script);

  
  //echo($html);dump($pageElements));

  $template_id = $pageObj->template_id ?: $siteObj->template_id;
  if($template_id == ADMIN_TEMPLATE_ID && $admin_menu) $pageElements->admin_menu = $admin_menu; // special case for admin pages (back-office);
  
  if($options['content']) { // no template
    $body = $options['content'];
  } else {    
    if($pageElements) $html = html_template($html, $pageElements);
    //$buttons_str = implode("\n", $buttons);
    $body = $lang_menu.$html;
    if($wrap_class = $options['wrap_content']) $body = html_div($body, $wrap_class);
  }
  
  $body_class = $options['body_class'] ? " class='$options[body_class]'" : '';
  $edit_menu = $auth_edit ? $_SESSION['__edit_menu'] : '';
  $output = "
<body id=\"page_".str_replace(' ', '-', strtolower($pageObj->name))."\"$body_class data-id=\"".$pageObj->id."\">
  $google_tag_manager
  $fb_sdk
  $edit_menu
  <!--[if lte IE 8]><p class=chromeframe>Your browser is <em>ancient!</em> <a href=\"http://browsehappy.com/\">Upgrade to a different browser</a> or <a href=\"http://www.google.com/chromeframe/?redirect=true\">install Google Chrome Frame</a> to experience this site.</p><![endif]-->
$body
$scripts_html
</body>
";
  return $output;
}

function site_header_var($siteObj, $pageObj, $var) {
  $fld = 'se_'.$var;
  $val = $pageObj->$fld ?: $siteObj->$fld;
  return parse_header_vars($siteObj, $pageObj, $val);
}

function parse_header_vars($siteObj, $pageObj, $var) {
 global $city_name;   
 global $site_name;   
 global $apt_name; 
 global $geo_name;
 $country_name  = $_SESSION['geo_country_name'];
 $district_name = $_SESSION['geo_district_name'];
 $path_var = ucfirst(str_replace('-', ' ', $_SESSION['path_var']));
 return ucfirst(trim(str_replace(array('__pagename', '__sitename', '__city', '__district', '__country', '__aptname', '__pathvar'), array($pageObj->title ?: $pageObj->menu_title, $site_name, $city_name, $district_name, $country_name, $apt_name, $path_var), $var))); 
}  

function site_spider_meta($siteObj, $pageObj) {
  $no_index  = $siteObj->no_index || $pageObj->no_index;
  $no_follow = $siteObj->no_follow || $pageObj->no_follow;  
  if(!$no_index && !$no_follow) return ''; 
  if($no_index && $no_follow) return '<meta name="robots" content="noindex, nofollow">'; 
  if($no_index) return '<meta name="robots" content="noindex, follow">'; 
  return '<meta name="robots" content="index, nofollow">'; 
}


// The doctype, <html>, and <head> tags for the site
function site_head($siteObj, $pageObj, $options=NULL) {
  //if($media == 'print') return html_head_print($siteObj); // special header for printable view
  // if(isset($_GET['print'])) $media = 'print';
  //die("in use ?");
  global $__header;
  global $u, $u_id;

  $can_edit = $options['can_edit'];
  $media = $options['css_media'] ?: 'screen';
  $framework = $pageObj->framework ?: $siteObj->framework;
  $bootstrap = $_SESSION['bootstrap'] = $framework == 'bootstrap';
  $sass = $_SESSION['sass'] = $framework == 'bootstrap-sass';
  // dump($options);
  
  $site_name = $siteObj->name;  
  $se_title = $__header['title'] ?: strip_tags(site_header_var($siteObj, $pageObj, 'title'));
  $se_keyw = $__header['keywords'] ?: strip_tags(site_header_var($siteObj, $pageObj, 'keywords'));
  $se_desc = $__header['description'] ?: strip_tags(site_header_var($siteObj, $pageObj, 'description'));
  
  // die("se_desc={$se_desc} hdr:".$__header['description'].dump($pageObj,true));
  
  $se_author = $__header['author'] ?: $site_name;

  
  global $meta_expires;
  $host_sub = $_SESSION['host_sub'];
  $spider = $host_sub == 'www' || !$host_sub ?  site_spider_meta($siteObj, $pageObj) : '<meta name="robots" content="noindex, nofollow">';
  //echo($spider);
  $expires = 3600*24*30; // 30 days
  //if(!$meta_expires) $meta_expires = date(DATE_RFC1123); // todo: allow to ovverride
  if(!$meta_expires) $meta_expires = gmdate('D, d M Y H:i:s', time()+$expires).' GMT';

  $jquery_version = $__header['jquery_version']  ?: '1.10.2'; // 1.7..3 not on google yet need to load now or else inline code won't work

  $jquery_ui_version = '1.11.4';  

  $lang = $_SESSION['language'];
  // $css_id = pick_first(array($_GET['_tid'], $pageObj->css_id, $siteObj->css_id));


  $cam_echo = false;
  $cam_minify = 1;
  $cam_postfix = '_3'; // for cache busting for now
  
  if($onload = $__header['onload']) {
    
    if($_SESSION['combine_and_minify']) {
      $finalized = '$(document).bind("finalized",function(){'.$onload.'});'; // this allows us to call onload for dynamically loaded content
      $onload_script = '$(document).ready(function() {$(document).trigger("finalized");});'.$finalized; 
      $end_scripts = combine_and_minify_js($siteObj, NULL, $onload_script, array('minify' => $cam_minify, 'echo' => $cam_echo, 'output' => 'mods/onload'.$cam_postfix, 'inline' => 1));;
      $__header['end_scripts'] = array_merge($__header['end_scripts'], $end_scripts);
    } else {
      $onload_script = '$(document).ready(function() {'.$onload.'});'; 
      $onload_str = html_script_inline($onload_script);
    }
  } 
  
  // base styles
  $cache_bust = $_SESSION['dev'] || $_SESSION['test'] ? "?ts=".time() : "?ver=".$_SESSION['version'];
  $cache_bust2 = $cache_bust ? str_replace('?', '&', $cache_bust) : '';
  $aid = $_SESSION['aid'];

  if($options['base_styles'] === false ) {
    //die("gh1234");
    $styles = $__header['base_css'] ?: array();
    $base_scripts = $__header['base_scripts'] ?: array();
    // do not load any base styles
  } elseif($sass) {
    $styles= array(
//      'http://sass.syspensa.com/stylesheets/screen.css',
      '/afr/css/afr_base.css',
      '/afr/css/sass-screen.css',
      //'/afr/css/afr.css',             
      //'/afr/bower/bootstrap/dist/css/bootstrap.min.css',             
      '//netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap-glyphicons.css',      
      'http://fonts.googleapis.com/css?family=Open+Sans:300italic,400italic,600italic,700italic,800italic,400,700,600,300,800',
      '/afr/bower/fancybox/source/jquery.fancybox.css',
      '/afr/bower/fontawesome/css/font-awesome.min.css',
      '/afr/bower/zocial/css/zocial.css',
      '/afr/css/fontello-7a3c0263/css/fontello.css',
      '/css/site.css'.$cache_bust,             
    );
    if($siteObj->theme) $styles[] = "/afr/css/themes/".$siteObj->theme;
    $base_scripts = array(
      '/afr/bower/jquery/dist/jquery.min.js',
      //'script:$.widget.bridge("uibutton", $.ui.button);$.widget.bridge("uitooltip", $.ui.tooltip);',
      '/afr/bower/bootstrap-sass-official/assets/javascripts/bootstrap.js',
      '/afr/bower/bootstrap-hover-dropdown/bootstrap-hover-dropdown.min.js',
      '/afr/bower/jquery-ui/ui/minified/jquery-ui.min.js',
      '/afr/bower/fancybox/source/jquery.fancybox.pack.js',
      '/afr/bower/jquery-form/jquery.form.js',
      '/afr/js/afr.js'.$cache_bust      
    );
  } else {
    //die("gh2");
    $styles= array(
       '/afr/css/afr_base.css'.$cache_bust,             
       '/afr/css/afr.css'.$cache_bust,             
       '/afr/css/afr_tooltip.css',             
       // '/css/style.css'.$cache_bust,             
       //'/css/style-static-test.css',             
       '/afr/css/zocial.css',             
       '/afr/css/fontello-7a3c0263/css/fontello.css',
    );
    if(!$options['no_style']) $styles[] = "/afr/css/site.css.php?s=$siteObj->id".($aid ? "&aid=$aid" : '').$cache_bust2;
    if($bootstrap) {
             
      
      $styles[] = "/afr/bower/fontawesome/css/font-awesome.min.css";
      $styles[] = "/afr/bower/bootstrap/dist/css/bootstrap.min.css";
      $styles[] = "/afr/bower/bootstrap/dist/css/bootstrap-theme.min.css";
      $styles[] = "/afr/bower/bootstrap-toggle/css/bootstrap-toggle.min.css";
      $styles[] = "/afr/bower/bootstrap-modal/css/bootstrap-modal-bs3patch.css";
      $styles[] = "/afr/bower/bootstrap-modal/css/bootstrap-modal.css";
      //$styles[] = "/afr/bower/bootstrap-datepicker/css/datepicker3.css";
      $styles[] = "https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.4.1/css/bootstrap-datepicker3.min.css";
      
    }
    $styles[] = '/afr/bower/fancybox/source/jquery.fancybox.css';
    
    
    // base scripts
    $base_scripts = array(
      '/afr/bower/jquery/dist/jquery.min.js',
      '/afr/bower/jquery-ui/ui/minified/jquery-ui.min.js',
      //'script:$.widget.bridge("uibutton", $.ui.button);$.widget.bridge("uitooltip", $.ui.tooltip);',
      '/afr/bower/jquery-form/jquery.form.js',
      '/afr/js/afr.js'.$cache_bust
    );
    if($bootstrap) {
      $base_scripts[] = '/afr/bower/bootstrap/dist/js/bootstrap.min.js'; //netdna.bootstrapcdn.com/bootstrap/3.1.1/js/bootstrap.min.js';
      $__header['end_scripts'][] = "/afr/bower/bootstrap-toggle/js/bootstrap-toggle.min.js";
      $__header['end_scripts'][] = "/afr/bower/bootstrap-modal/js/bootstrap-modalmanager.js";
      $__header['end_scripts'][] = "/afr/bower/bootstrap-modal/js/bootstrap-modal.js";      
      //$__header['end_scripts'][] = "/afr/bower/bootstrap-datepicker/js/bootstrap-datepicker.js"; 
      $__header['end_scripts'][] = "https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.4.1/js/bootstrap-datepicker.min.js"; 
      //$__header['end_scripts'][] = "/afr/lib/selectToAutocomplete/jquery.select-to-autocomplete.js";      
    }

    $base_scripts[] = '/afr/bower/fancybox/source/jquery.fancybox.pack.js';
    
  }
  //if(!$siteObj->no_terms) $base_scripts[] = '/afr/js/terms.js.php'.$cache_bust;

  // ui theme
  $jquery_ui_theme = $siteObj->jquery_ui_theme ?: 'ui-lightness';
  
  // hosted on http://jquery-ui.googlecode.com/svn/tags/1.8.23/themes/
  $hosted_themes = array("black-tie","blitzer","cupertino","dark-hive","dot-luv","eggplant","excite-bike","flick","hot-sneaks","humanity","le-frog","mint-choc","overcast","pepper-grinder","redmond","smoothness","south-street","start","sunny","swanky-purse","trontastic","ui-darkness","ui-lightness","vader");
  if(!in_array($jquery_ui_theme, $hosted_themes)) $jquery_ui_theme = "smoothness"; // fallback
  array_unshift($styles, '//ajax.googleapis.com/ajax/libs/jqueryui/'.$jquery_ui_version.'/themes/'.$jquery_ui_theme.'/jquery-ui.css');
  //elseif($jquery_ui_theme) array_unshift($styles, $jquery_ui_theme);

//ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/themes/smoothness/jquery-ui.css
//ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/themes/base/jquery-ui.css 

  $pt= $pageObj->page_type;
  //if($siteObj->show_types || ($pt && get_object('page_type', $pt, 'property'))) $base_scripts[] = '/afr/js/afr_property.js';
  if($siteObj->property_site || $siteObj->property_type) $scripts[] = "/afr/js/afr_rental.js?v=$ver";

  //<script>window.jQuery || document.write('<script src=\"/jquery/jquery-$jquery_version.min.js\"><\/script>')</script>
  $scripts_html = '';                          

  //if($framework == 'boilerplate') $scripts_html = "  <script src=\"/afr/js/modernizr-2.5.3.min.js\"></script>\n"; // not to be combined
  $scripts_html = "  <script src=\"/afr/bower/modernizr/modernizr.js\"></script>\n"; // not to be combined
  /** pdf experiment
  $scripts_html .= '
  <script src="/afr/bower/webcomponentsjs/webcomponents.min.js"></script>
  <link rel="import" href="/afr/bower/pdf-viewer/dist/pdf-viewer.html">
  ';
  */
  
  $styles_html = '';
  //if($bootstrap) $styles_html .= "<link href=\"/less/init.less\" rel=\"stylesheet/less\" type=\"text/css\">\n";
  if($_SESSION['combine_and_minify']) { // combine and minify js+css base (always loaded, same for every page, big files)
    //dump($styles);
    $styles = combine_and_minify_css($siteObj, NULL, $styles, array('minify' => $cam_minify, 'echo' => $cam_echo, 'output' => 'base'.$cam_postfix));  
    $base_scripts = combine_and_minify_js($siteObj, NULL, $base_scripts, array('minify' => $cam_minify, 'echo' => $cam_echo, 'output' => 'base'.$cam_postfix)); // let build script do this
    foreach($styles as $style) $styles_html .= "  <link rel=\"StyleSheet\" href=\"$style\" type=\"text/css\" media=\"$media\"$st>\n";
    foreach($base_scripts as $script) $scripts_html .= "  ".html_script($script);
    $styles = array();
    $scripts = array();
  } else {
    $scripts = $base_scripts;
  }
  
  // extended styles  
  if($css_file = $siteObj->css_file) $styles[] = $css_file; // site specific css file

  if($u_id) $styles = array_merge($styles, array(
   //'/jquery/colorpicker/css/colorpicker.css', 
    //'/afr/bower/jquery.colorpicker/jquery.colorpicker.css',                     
    //'/jquery/file-uploader-3.3/client/fineuploader.css',
    //'/afr/bower/fine-uploader/client/fineuploader.css',
    '/afr/bower/summernote/dist/summernote.css',
  ));


  if($aff_css = $_SESSION['aff_css']) $styles[] = "/afr/css/aff/$aff_css";
  if(count($__header['css'])) $styles = array_merge($styles, $__header['css']);
  $styles = array_unique($styles);
  /**
  if($u_id) $scripts = array_merge($scripts, array(
                     '/afr/js/afr_cms.js',     
                     //'/jquery/colorpicker/js/cp.min.js',
                     //'/afr/bower/jquery.colorpicker/jquery.colorpicker.js',                     
                     //'/jquery/file-uploader-3.3/client/js/client.min.js',
                     //'/afr/bower/fine-uploader/client/js/uploader.basic.api.js',
                     '/afr/bower/summernote/dist/summernote.min.js',
                     '/afr/bower/ckeditor/ckeditor.js',
                     '/afr/bower/ckeditor/adapters/jquery.js',
                     '/afr/ckfinder/ckfinder.js',
                     ));
                     */
  if(count($__header['scripts'])) {    
    $scripts = array_unique(array_merge($scripts, $__header['scripts']));
  }
  if(isset($_GET['__scripts'])) dump($scripts);

  // combine and minify css + javascript to cache directory (used by spider)
  if($_SESSION['combine_and_minify']) { // combine and minify js+css extra (differ per page, small files)
    $styles = combine_and_minify_css($siteObj, $pageObj, $styles, array('minify' => $cam_minify, 'echo' => $cam_echo, 'output' => 'extra'.$cam_postfix, 'hash' => true));  
    $scripts = combine_and_minify_js($siteObj, $pageObj, $scripts, array('minify' => $cam_minify, 'echo' => $cam_echo, 'output' => 'mods/extra'.$cam_postfix, 'hash' => true));  
  }

  //foreach($styles as $style) $styles_html .= "  <link rel=\"StyleSheet\" href=\"$style\" type=\"text/css\" media=\"$media\"$st>\n";
  foreach($styles as $style) $styles_html .= "  ".html_style_tag($style, "text/css", $media);
  foreach($scripts as $script) $scripts_html .= "  ".html_script($script);

  // fonts - only those listed here are allowed: http://www.google.com/webfonts
  $fonts = array();
  if(count($__header['fonts']))  $fonts = array_unique(array_merge($fonts, $__header['fonts']));
  foreach($fonts as $font) $fonts_html .= "  ".html_font($font);
  
  if($google_analytics_id = $siteObj->google_analytics_id) $google_tracker = google_tracker($google_analytics_id);   

  $full_path = site_full_url($siteObj).$pageObj->path;
  if($path_var = $_SESSION['path_var']) $full_path .= "$path_var/";

  if($_SESSION['combine_and_minify']) {
    $_SESSION['async'] = true; // use jQl async loader
    if($_SESSION['async']) {
      $jq_load  = "jQl.loadjQ('".$base_scripts[0]."');\n"; // should just be one (base)
      $jq_load .= "jQl.loadjQdep('".$scripts[0]."');\n"; // should just be one (extra)
      $scripts_html = jQl($jq_load);    
    } else {
      $__header['end_scripts_html'] = $scripts_html;
      $scripts_html = '';    
    }
  }
  
  $meta_html = '';
  $metas = $__header['meta'] ?: array();
  foreach($metas as $meta) {
    $meta_html .= html_meta($meta)."\n";  
  }

  $link_html = '';
  $links = $__header['link'] ?: array();
  foreach($links as $link) {
    $link_html .= html_header_link($link)."\n";  
  }

  $canonical = $__header['canonical'] ?: $full_path;

  $shim = $sass ? '
  <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
  <!-- WARNING: Respond.js doesn\'t work if you view the page via file:// -->
  <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="/afr/bower/respond/respond.js"></script>
  <![endif]-->
  ' : '';
  
  
  $favicon = is_file(docroot()."favicon.ico") ? '<link rel="icon" type="image/ico" href="/favicon.ico"' : "";
  $favicon = is_file(docroot()."favico.ico") ? '<link rel="icon" type="image/ico" href="/favicon.ico"' : "";
  $output = "
<head>
  <meta charset=\"utf-8\">
  <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">

  <title>$se_title</title>
  <meta name=\"description\" content=\"$se_desc\">
  <meta name=\"keywords\" lang=\"$lang\" content=\"$se_keyw\">
  <meta name=\"author\" lang=\"$lang\" content=\"$se_author\">
  $fav_icon
  $spider
  $meta_html
  $link_html
  $styles_html
  $fonts_html
  <link rel=\"canonical\" href=\"$canonical\" />
  <link rel=\"stylesheet\" href=\"/afr/css/print.css\" type=\"text/css\" media=\"print\">
  $scripts_html
  $google_tracker
  $shim  
  {$pageObj->header_code}
</head>
";

  return $output;
}

function site_html($siteObj, $pageObj, $options=NULL) {    
  if($template_id = ($pageObj->template_id ?: $siteObj->template_id)) return get_object('site_template', $template_id, 'html');
  return '';
}

// finds the home page for given language
function site_home_page($siteObj_or_id, $lang='') {
  if(!$lang) $lang = $_SESSION['lang'];
  $siteObj = any2obj('site', $siteObj_or_id);
  $homePageObj = find_object('site_page', array('site_id' => ($siteObj->parent_site_id ?: $siteObj->id), 'page_type' => PAGE_HOME)); // home page
  return site_find_content($siteObj, $homePageObj, $lang);
}


// returns site-page merged with site-content for given path and site  
function site_find_page($siteObj, $path) {
  $contentSearch['path'] = $path;
  $contentSearch['page_content.site_id'] = $siteObj->id;
  $sort = "page_content.site_id DESC";
  //dump($contentSearch);
  if($pageContentObj = find_object('page_content', $contentSearch, '', array('sort' => $sort))) {
    //dump($pageContentObj);
    return site_page_object($pageContentObj);
  }
  return NULL;
}

// finds content for this page (for correct site and language)
function site_find_content($siteObj_or_id, $pageObj_or_id, $lang='') {

  $site_id = any2id('site', $siteObj_or_id);
  $page_id = any2id('site_page', $pageObj_or_id);  
  if($pageContentObj = find_object('page_content', ['site_id' => $site_id, 'page_id' => $page_id, 'language' => $lang ?: $_SESSION['language']])) return site_page_object($pageContentObj, $pageObj);
  return any2obj('site_page', $pageObj_or_id);
}


// full URL of any site
// without trailing slash

function site_full_url($siteObj_or_id, $trailing_slash = false) {    
  $url = SITE_URL ?: siteURL(); // from current URL;
  $url = rtrim($url, '/'); // remove trailing
  return $trailing_slash ? "{$url}/" : $url; // add trailing if set
}

function site_url($siteObj_or_id) {  
  $siteObj = any2obj('site', $siteObj_or_id);
  $protocol = $siteObj->secure ? 'https' : 'http';
  $sub = $_SESSION['host_sub'] ?: '';
  if($sub) $sub = "{$sub}.";
  return "{$protocol}://{$sub}{$siteObj->domain}";
}


// searches for page by type (or name) for given site (obj or id)
// returns first found if multiple hits (by default sort)
// if page_type is a string instead of numeric, it searches by name instead of page type 
function site_find_pagetype($siteObj, $page_type, $lang='', $options=NULL) {
  
  $pageSearch = $options['search'];
  $pageSearch['site_id'] = $siteObj->parent_site_id ?: $siteObj->id;
  $pageSearch['active'] = 1;

  if(isint($page_type)) $pageSearch['page_type'] = $page_type;
  else $pageSearch['name'] = $page_type;


  $pageObj = find_object('site_page', $pageSearch);
  $result = $pageObj;
  
  if($pageObj && $lang) { // return content with corresponding language
    $contentSearch['page_id'] = $pageObj->id;
    $contentSearch['page_content.site_id'] = $siteObj->id;
    $contentSearch['language'] = $lang;
    if($pageContentObj = find_object('page_content', $contentSearch)) $result =  site_page_object($pageContentObj, $pageObj);
  }
  if($field = $options['field']) return $result->$field;
  return $result;
}

/** smarty alias for get_page, returns array instead of object */
function smarty_get_page($pageObj_or_id, $lang='') {
  return (array) get_page($pageObj_or_id, $lang);
}

function smarty_page_content($page_type, $options=[]) {
  return (array) page_content($page_type, $lang);
}

/** alias for site_find_content */
function get_page($pageObj_or_id, $lang='') {
  return site_find_content($_SESSION['siteObj'], $pageObj_or_id, $lang);
}

/** new: used by Smarty; find by page_type, optionally language/object_type/object_subtype */
function page_content($page_type, $options=[]) {
  global $__SITE, $__LANG;
  $pSearch['site_id'] = $__SITE->id;
  $pSearch['page_type'] = $page_type;
  $pSearch['active'] = 1;
  if($obj_type = $options['object_type']) $pSearch['object_type'] = $obj_type;
  if($obj_subtype = $options['object_subtype']) $pSearch['object_subtype'] = $obj_subtype;
  $pageObj = find_object('site_page', $pSearch);
  if(!$pageObj) return null; /** throw exception */
  
  $lang = pick_first($options['language'], $options['lang'], $__LANG, $__SITE->default_language);
  
  $cSearch = array('page_id' => $pageObj->id, 'language' => $lang);
  
  return find_object('page_content', $cSearch, $options['field'] ?: $options['fields']);
}

/** new: used by Smarty; find by page_type/object_type/object_subtype */
// todo: put obj_type/subtype in options
function page_link($page_type, $obj_type='', $obj_subtype='', $options=[]) {
  if($obj_type) $options['object_type'] = $obj_type;
  if($obj_subtype) $options['object_subtype'] = $obj_subtype;  
  $pageObj = page_content($page_type, $options);
  return $pageObj->path;
}


/** new: used by Smarty; print html_link with name/path given page_id */
/** optional: full,  */
function print_page_link($page_id, $options = array()) {
  $pageObj = get_page($page_id);
  $qs = $options['qs'] ? "?{$qs}" : "";
  return html_link($pageObj->path, pick_first($pageObj->menu_title, $pageObj->title, $pageObj->name)).$qs;
}

// return links for given site/page_type/language if found
function site_pagetype_link($site, $page_type, $lang='', $linkonly=true, $full=false) {
  $siteObj = any2obj('site', $site);
  $pSiteObj =  ($pid = $siteObj->parent_site_id) ? get_object('site', $pid) : $siteObj;
  $pageObj = site_find_pagetype($pSiteObj, $page_type);
  return $pageObj ? site_page_link($siteObj, $pageObj, array('linkonly' => $linkonly, 'full' => $full, 'lang' => $lang)) : '';  
}

// return links for given site/page_object/language if found
function site_page_link($siteObj_or_id, $pageObj_or_type, $options=NULL) {
  global $__LANGUAGES, $__LANG;
  $siteObj = any2obj('site', $siteObj_or_id);
  
  $lang = pick_first($options['lang'], $options['language'], $__LANG);
  $geoObj = $_SESSION['geoObj'];
  $linkonly = isset($options['linkonly']) ? $options['linkonly'] : true;
  $full = $options['full'];
  $pageObj = isint($pageObj_or_type) ? site_find_pagetype($siteObj, $pageObj_or_type, $lang, $options) : $pageObj_or_type; 

  $site_langs = $__LANGUAGES;
  if(!$lang || !in_array($lang, $site_langs)) $lang = $_SESSION['lang'] ?: $siteObj->default_language;
  
  if($gdir = ($options['city_dir'] ?: $options['geo_dir'])) {
    $geodir = '/'.trim($gdir, '/').'/';
    //echo("spl: cd=$geodir<br>");
  } elseif($pageObj->relative && $geoObj) {
    $geodir = loc_link($geoObj->level, $geoObj->fid, $lang, true, true);    
  }

  //dump($geoObj);echo("geodir = $geodir<br>");
  $content = isset($pageObj->lang) && $lang == $pageObj->lang ? $pageObj : site_find_content($siteObj, $pageObj, $lang);
  if($content->site_id != $siteObj->id) { // alternate site    
    $siteObj = get_object('site', $content->site_id);
    $full = true;
  }
  
  if(!$content) {
    return '';
  }
  
  $link = $content->path;
  if($pageObj->relative && $geodir) {
    if(strpos($link, "/$lang/") === 0) $link = '/'.$lang.$geodir.substr($link, 4); // put lang first like /nl/rotterdam/path/
    else $link = $geodir.ltrim($link, '/');
  }
  if($link[0] != '/') $link = "/$link"; // always start with slash
  $aid = $options['aff_id'] ?: $_SESSION['aff_id'];
  $aff_type = $options['aff_type'] ?: $_SESSION['aff_type'];
  if($aid) { // add affiliate prefix if needed
    //$prefix = $_SESSION['showing_partners'] ? 'aidp' : 'aid';
    if(strpos($link, "aid$aff_type$aid") === FALSE) $link = "/aid$aff_type$aid".$link;                                
  }
  $link = clean_path($link);
  if($full) $link = site_url($siteObj).$link;
  return $linkonly ? $link : html_link($link, $options['name'] ?: $content->menu_title);
}

// $p can be a page_type (int), pageObj (object or array), or pageObj->name (string)
function get_page_link($p, $linkonly=true, $lang="", $name="", $city_dir='', $full=false) {
  $siteObj = $_SESSION['siteObj'];
  if($pid = $siteObj->parent_site_id) $siteObj = get_object('site', $pid);
  if(!$lang) $lang= $_SESSION['language'] ?: $siteObj->default_language;
  //dump($p);
  if(isint($p)) {
    $pageObj = site_find_pagetype($siteObj, $p); // received page_type
  } else {
    if(is_array($p)) $p = array2obj($p);
    $pageObj = is_object($p) ? $p : find_object('site_page', array('site_id' => $siteObj->id, 'name' => $p));
  }
  if(!$pageObj) return '';
  $options['linkonly'] = $linkonly;
  $options['full'] = $full;
  $options['lang'] = $lang;
  $options['name'] = $name;
  $options['city_dir'] = $city_dir;
  //dump($options);
  return site_page_link($_SESSION['siteObj'], $pageObj, $options);
}

// returns parent, or parent of parent etc until given level (0 is root)                                                      
function site_get_ancestor($siteObj, $pageObj, $level=0) {
  if($level == '') $level = 0;
  $ancestorObj = $pageObj;
  while($ancestorObj->level > $level) {
    //dump($ancestorObj);    
    // die("al=$ancestorObj->level level=$level");
    $ancestorObj = get_object('site_page', $ancestorObj->parent_id);
  }
  return site_find_content($siteObj, $ancestorObj, $_SESSION['lang']) ?: $ancestorObj;
}


// returns the id for an editable element
function site_edit_id($siteObj_or_id, $pageObj_or_id, $can_edit, $obj_type, $fields, $id, $options=NULL) {
  //dump($options['data']);
  //global $__header;
  $site_id = is_object($siteObj_or_id) ? $siteObj_or_id->id : $siteObj_or_id;
  $page_id = is_object($pageObj_or_id) ? $pageObj_or_id->id : $pageObj_or_id;
  
  if(is_array($fields)) $fields = implode('|', $fields);        
  if(!$can_edit) return $id=$options['id'] ? $id : "";

  $action = $options['action'] ?: 'edit';
  $site_id = $options['site_id'] ?: $site_id;
  $page_id = $options['page_id'] ?: $page_id;
  $lang    = $options['language'] ?: $_SESSION['language'];
  $parent_id = ($options['parent_id'] ?: $options['data']['parent_id']) ?: 0;
  $type = $options['type'] ?: 0;

  $id = implode('-', array($action,$obj_type,$fields,$id,$site_id,$page_id,$lang, $parent_id, $type));
  return $id;
  
  //if($data = $options['data']) $__header['onload'] .= '
  //  $("#'.$id_str.'").data("data", '.json_encode($data).'); 
  //';
  //return "id=$id_str";    
  //return "id='$action-$obj_type-$fields-$id-$site_id-$page_id-$lang'";
}

function redirect_login($ref='') {
  global $__SITE;  
  if($_GET['_new'] == "register") {
    unset($_GET['_new']);
    $login_page = site_page_link($__SITE, PAGE_REGISTER);      
  } else {
    $login_page = site_page_link($__SITE, PAGE_LOGIN);
  }
  
  if(!$ref) $ref = $_SESSION['referring_page'] = ($_SERVER['REDIRECT_URL  '] ?:$_SERVER['REQUEST_URI']);
  $ref = str_replace('act=logout', '', $ref);
  redirect("{$login_page}?ref=".urlencode($ref));    
  die("<a href='/admin/login.php'>Please log in to access this page</a>");                                                        
}


// returns page_content merged with parent page
function site_page_object($content, $pageObj=NULL) {
  $pageContentObj = is_object($content) ? clone $content : get_object('page_content', $content);      
  if(!$pageObj) $pageObj = get_object('site_page', $pageContentObj->page_id); 
  return site_merge_page_object($pageObj, $pageContentObj);
}                            

// merges content fields from contentPageObj with pageObj
function site_merge_page_object($pageObj, $pageContentObj) {
  $mergedPageObj = is_object($pageObj) ? clone $pageObj : $pageObj;
  if(!$pageContentObj) return $mergedPageObj;
  foreach($pageContentObj as $k => $v) {
    if($k == 'id') $k = 'content_id';
    $mergedPageObj->$k = $v; // merge as one
  }
  return $mergedPageObj;
}

/** new edit menu */
function site_edit_menu($siteObj, $pageObj, $options = array()) {
  if(!$siteObj || !is_object($siteObj)) return '';
  if(!$pageObj || !is_object($pageObj)) return '';
  
  $url = this_url();
  
  $buttons = array();
  if($_SESSION['__edit_mode']) {
    $buttons[] = html_link(replace_query_var($url, '__edit_mode', 0), "<i class='fa fa-times-circle'></i> Exit Edit Mode", array('class' => 'btn btn-danger __edit_site __edit_on'));
  } else {
    $buttons[] = html_link(replace_query_var($url, '__edit_mode', 1), "<i class='fa fa-pencil-square-o'></i> Edit Content", array('class' => 'btn btn-success __edit_page'));
    $buttons[] = html_link("#page-form-modal", "<i class='fa fa-plus-square'></i> Add Page", array('class' => 'btn btn-success __add_page reset-form', 'data-toggle' => "modal", 'data-backdrop' => "static", 'data-form' => '#page-form'));
    $clone = clone $pageObj;
    unset($clone->content);    
    $buttons[] = html_link("#page-edit-form-modal", "<i class='fa fa-file-text-o'></i> Edit Page", array('class' => 'btn btn-success __edit_page fill-form', 'data-toggle' => "modal", 'data-backdrop' => "static", 'data-form' => '#page-edit-form', 'data-data' => $clone));
    
    $children = find_objects('site_page', array('parent_id' => $pageObj->id));
    if($pageObj->page_type != PAGE_HOME && !$children) 
      $buttons[] = html_link("#", "<i class='fa fa-times'></i> Delete Page", 
         array('class' => 'btn btn-danger __delete_page', 
           'data-obj_type' => 'site_page', 'data-obj_id' => $pageObj->id,
           'data-toggle' => 'confirmation', 'data-placement' => 'bottom', 'data-on-confirm' => 'delete_object', 'data-redirect' => '/'
           ));

    $edit_site_url = site_page_link($siteObj, PAGE_EDIT_SITE);
    $buttons[] = html_link($edit_site_url, "<i class='fa fa-sitemap'></i> Edit Site", array('class' => 'btn btn-success __edit_site'));
    $is_writable = $is_file = false;
    if($template = $pageObj->template) {
      //list($filename, $ext) = split_filename($template);
      $filename = str_replace(".html", "", $template);
      $file = clean_path(docroot()."/pages/$filename".'.html');    
      $is_writable = is_writable($file);
      $is_file = is_file($file);
      if($is_file && $is_writable) {
        $buttons[] = html_link("#", "<i class='fa fa-code'></i> Edit Template", array('class' => 'btn btn-success __edit_template', 'data-template' => $file));
      }
    }
    $text = "";    
    if($pageObj->template) {
      $text .= "Template: $pageObj->template (";
      $text .= $is_file ? "File exists" : html_span("$file does not exist template=$template", 'red');
      if($is_file) $text .= $is_writable ? " and is writable" : " but is not writable";
      $text .= ") ";
    }
    //if($count = count($children)) $text .= " Page has $count children (cannot be deleted)";
    if($pageObj->controller) $text .= " Controller: $pageObj->controller";
    $text = html_span($text, "margin-left text-success", array("style" => ""));

  }
  

  $output = implode(PHP_EOL, $buttons);
  if($text) $output .= html_div($text);
  //$output = "Foo";
  return html_div($output, 'hidden abs_top_left-off', array('id' => "site_edit_panel"));
}

/** new forms for editing page, later site */
function site_edit_forms($siteObj, $pageObj, $options = array()) {
  global $u_level, $u_id;
  $auth_edit = $u_id && $u_level >= USER_LEVEL_STAFF;
  if(!$auth_edit) return '';
    
  $page_templates = array();
  if($template = $siteObj->template) {
    $template_dir = "/web/templates/{$template}/stripped/";
    $page_templates = file_array($template_dir);
  }

  $forms = '';
  $forms .= smarty_parse_template($siteObj, $pageObj, 'afr/pages/page-form.html', array('page_templates' => $page_templates));    
  $forms .= smarty_parse_template($siteObj, $pageObj, 'afr/pages/page-edit-form.html', array('page_templates' => $page_templates));    
  
  //list($filename, $ext) = split_filename($pageObj->template);
  $template = $pageObj->template;
  $filename = rtrim($template, '.html').'.html';
  $template_file = clean_path(docroot()."/pages/$filename");    
  $forms .= smarty_parse_template($siteObj, $pageObj, 'afr/pages/_template-edit-form.html', array('filename' => $template_file));
  
  //die("ok uid = $u_id l=$u_level auth=$auth_edit forms=$forms");
 
  return $forms;
}

// automatically adds all pages for a site for which cms_add is set in page_type
// currently: home, about, contact
function site_add_default_pages($siteObj_or_id, $options=NULL) {

  $echo = $options['echo'];
  $update = isset($options['update']) ? $options['update'] : true;

  $page_types = array();
  $siteObj = any2obj('site', $siteObj_or_id);
  if($siteObj->parent_site_id) return; // don't add any pages, only parent site has pages
  if($echo) echo(html_h3($siteObj->name));
  $pages_to_add = $siteObj->add_pages ?: 0; 
  $pages_to_add |= CMS_ADD_ALWAYS;
  if($show_types = $siteObj->show_types) {
    $pages_to_add |= CMS_ADD_PROPERTY; // this is a property site, add property related pages
    $page_types = find_objects('page_type', array('property' => explode(',', $show_types))); // add shortstay, boat, etc
  }
  if($siteObj->allow_user_login) $pages_to_add |= CMS_ADD_USER_LOGIN;
  if($siteObj->allow_user_register) $pages_to_add |= CMS_ADD_USER_REGISTER;
  if($siteObj->gallery_site) $pages_to_add |= CMS_ADD_GALLERY;
  if($siteObj->payment_options) $pages_to_add |= CMS_ADD_PAYMENTS;

  $pageTypeObjs = find_objects('page_type');
  foreach($pageTypeObjs as $pageTypeObj) {
    //echo("$pageTypeObj->name = $pageTypeObj->cms_add   $pageTypeObj->cms_add & $pages_to_add = ").($pageTypeObj->cms_add & $pages_to_add).html_break();
    if($pageTypeObj->cms_add & $pages_to_add) {
      //if($echo) echo("  $pageTypeObj->name: yes".html_break());
      $page_types[] = $pageTypeObj;
    }
  }
  
  $messages = array();
  $errors = array();
  $ids = array();
  //$update = false;$echo=true;  
  //dump($page_types);
  foreach($page_types as $page_type) {
    list($page_id, $page_errors, $page_messages) = site_add_page_type($siteObj, $page_type, $options);
    $ids[] = $page_id;
    $messages = array_merge($messages, $page_messags);
    $errors = array_merge($errors, $page_messags);
  }
  //if($echo) echo(print_errors($errors).print_messages($messages));
  return array($errors, $messages);
}

function site_update_content($siteObj) {
  return site_add_content($siteObj, false);
}


// adds site_content for a given site for each language
function site_add_content($siteObj, $add=true) {
  global $__LANGUAGES;
  $errors = array();
  $site_id = $siteObj->id;
  $languages = json_decode($siteObj->languages);
  if($languages[0] != $siteObj->default_language) { // make sure default language is first
    array_unshift($languages, $siteObj->default_language);
    $languages = array_unique($languages);
  }
  
  //dump($languages);
  foreach($languages as $lang) {
    $contentData->site_id = $site_id;
    $contentData->language = $lang;
    $contentObj = find_object('site_content', $contentData);  
    if($contentObj->page_id) {
      $content_id = $contentObj->id;
      echo("Found site_content for $siteObj->domain and language = $lang<br>");
      // list($cid, $cerrors) = update_object('site_content', $contentData, $content_id);
      // if($cerrors) $errors = array_merge($errors, $cerrors);
    } else {
      // $errors[] = "Could not find $lang content for page $pageObj->id ($pageObj->name)";
      //$contentData->title = $contentData->se_title = $contentData->menu_title = $title = site_page_name($pageObj, $lang);
      echo("Adding site content for $siteObj->name in $lang<br>");
      $contentData->title = $siteObj->name;
      list($cid, $cerrors) = add_object('site_content', $contentData);
      if($cerrors) $errors = array_merge($errors, $cerrors);
      else $ids[] = $cid;
    }

  }
  if($errors) dump($errors);
  return array($ids, $errors);
}

function site_update_content_pages($siteObj, $pageObj) {
  return site_add_content_pages($siteObj, $pageObj);
}



// sitemap

// returns array of all pages in same language as $pageObj for given site
// used to display HTML sitemap and to generate XML sitemap
function site_sitemap($siteObj_or_id, $options) {
  $siteObj = any2obj('site', $siteObj_or_id);
  $tree = site_sitemap_tree($siteObj, $options);
  return $tree;    
}

// recursively returns tree of pages in given language for given site 
function site_sitemap_tree($siteObj_or_id, $options=NULL) {
  $siteObj = any2obj('site', $siteObj_or_id);
  $lang = $options['language'] ?: $_SESSION['language'];
  $parent_id = isset($options['parent_id']) ? $options['parent_id'] : -1;
  if(!$lang) $lang = $siteObj->default_language; // todo: all languages    
  if(!$lang) die("site_sitemap_tree: language was not specified and $siteObj->domain has no default language");
  $tree = array();
  $parent_id = $options['parent_id'] ?: 0;
  $search = array('site_id' => $siteObj->parent_site_id ?: $siteObj->id, 'active' => 1, 'parent_id' => $parent_id, 'user_level' => 0, 'path_var' => '');
  $pageObjs = find_objects('site_page', $search, ['sort' => 'rank']);
  $count = count($pageObjs);
  foreach($pageObjs as $pageObj) {
    $node = site_sitemap_node($siteObj, $pageObj, $lang);
    if(!$node) continue;
    
    $options['parent_id'] = $pageObj->id;
    $children = site_sitemap_tree($siteObj, $options);
    $node->child_count = count($node->children);
    $node->children = $children;
    $tree[$node->path] = $node;
  }
  return $tree;
}



function site_write_sitemap($siteObj_or_id, $lang='') {
  $siteObj = any2obj('site', $siteObj_or_id);
  $doc_dir = site_directory($siteObj);
  if(!$doc_dir) return;
                      
  
  $xml = site_sitemap_xml($siteObj_or_id);
  
  $base_dir = $_SERVER['DOCUMENT_ROOT']."sites/$siteObj->domain/";
  $xmlfile = $base_dir.'sitemap.xml';
  write_file($xmlfile, $xml);
  $size = strlen($xml);
  echo("Wrote $size bytes to $xmlfile<br>");
  return $size;
}


function site_sitemap_xml($siteObj_or_id, $options = []) {  
  $siteObj = any2obj('site', $siteObj_or_id);
  $tree = isset($options['tree']) ? $options['tree'] : site_sitemap_tree($siteObj, $options);
  $urlset = site_sitemap_xml_nodes($siteObj, $tree);
  
  $xml = "<?xml version=\"1.0\" encoding=\"utf-8\"?>
  <urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\" 
   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
   xsi:schemaLocation=\"http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd\">;
{$urlset}
</urlset>";
      
  return $xml;
}

// print sitemap tree as XML
function site_sitemap_xml_nodes($siteObj_or_id, $nodes) {
  $site_url = rtrim(site_full_url($siteObj_or_id), '/');
  
  foreach($nodes as $path => $node) {
    if(strpos($path, 'http') !== 0) {
      $path = "{$site_url}{$path}";
      //die("no http, now $path");
    }
    $xml .= "
  <url>
    <loc>".$path."</loc>
  </url>";
    if($node->children) $xml .= site_sitemap_xml_nodes($siteObj_or_id, $node->children);
  }
  return $xml;
//    $priority = $node->priority ?: '0.5';
//    $change_freq = $node->change_freq ?: 'daily';
//    <priority>".$priority."</priority>
//    <changefreq>".$change_freq."</changefreq>

}


    
// recursively returns tree of pages in given language for given site
// called from site_menu_tree
function site_page_tree($siteObj_or_id, $options=NULL) {
  $search = $options['search'] ?: array('site_id' => $siteObj->parent_site_id ?: $siteObj->id, 'active' => 1, 'show_menu' => 1);
  $siteObj = any2obj('site', $siteObj_or_id);
  $lang = $options['language'];
  $parent_id = isset($options['parent_id']) ? $options['parent_id'] : -1;
  if(!$lang) $lang = $siteObj->default_language; // todo: all languages    
  if(!$lang) die("site_page_tree: language was not specified and $siteObj->domain has no default language");
  $tree = array();
  $root = 0;
  if($parent_id == -1) { // root
    $root = 1;
    $homePage = site_home_page($siteObj, $lang);
    if(!$homePage) echo("Warning: could not find home page for $siteObj->domain");
    $options['parent_id'] = 0;
    $root_node = site_sitemap_node($siteObj, $homePage, $lang);
    $children = site_page_tree($siteObj, $options);
    $root_node->child_count = count($children);
    $root_node->children = $children; // recurse the rest
    $tree[$root_node->path] = $root_node;
  }
  $parent_id = $options['parent_id'];
  
  //$search = array('site_id' => $siteObj->parent_site_id ?: $siteObj->id, 'active' => 1, 'parent_id' => $parent_id, 'admin' => 0);
  
  $search['parent_id'] = $parent_id;
  if(!$parent_id) $search['page_type'] = array('!=', PAGE_HOME); // this is only needed for top level 
  $pageObjs = find_objects('site_page', $search, array('sort' => 'rank'));
  $count = count($pageObjs);
  foreach($pageObjs as $pageObj) {
    $node = site_sitemap_node($siteObj, $pageObj, $lang);
    if(!$node) continue;
    
    $options['parent_id'] = $pageObj->id;
    $children = site_page_tree($siteObj, $options);
    $node->child_count = count($children);
    $node->children = $children;
    //dump($node);
    $tree[$node->path] = $node;
  }
  
  //dump($tree);die();
  return $tree;
}
  

// a node is just the fields of pageContent we care about (+ its children, set in site_sitemap_tree)
function site_sitemap_node($siteObj, $pageObj, $lang='') {
  $node = new stdClass;
  $node->page_id = $pageObj->id;
  if($pageObj->path) {
    $pageContent = $pageObj;
    $lang = $pageContent->language;
  } else if($lang) {
    $pageContent = site_find_content($siteObj, $pageObj, $lang);
  } else {
    die("site_sitemap_node: neither page content nor language passed");
  }
  
  if(!$pageContent) return NULL;
  $node->content_id = $pageContent->content_id;
  $copy_flds = array('title', 'menu_title', 'user_level', 'page_type', 'is_folder'); 
  foreach($copy_flds as $fld) $node->$fld = $pageContent->$fld;

  if($node->is_folder) { 
    $node->name = $pageObj->name;
    $node->path = $pageContent->path;
  } else {  
    //dump($pageContent); 
    $node->se_title = site_header_var($siteObj, $pageObj, 'title');
    $node->path = $pageContent->path;
    $node->url = site_page_link($siteObj, $pageContent, array('full' => true, 'lang' => $lang));
    $node->name = pick_first(array($pageContent->menu_title, $pageContent->title, $pageContent->se_title, $pageObj->name));
    $node->lang = $lang;
    $node->show_menu = $pageObj->show_menu;  
    $node->user_level = $pageObj->user_level;
    
    if($page_type = $node->page_type) {
      $pageTypeObj = get_object('page_type', $page_type);
    }
  } 
  //dump($node);                    
  //echo("$node->name<br>");
  return $node;
}


/** new 2016, used by jstree in edit-site */
function site_tree($siteObj_or_id, $options=NULL, $parent_id=0) {
  global $u_id, $u_level, $__LANG;
  
  $lang = isset($options['language']) ? $options['language'] : $__LANG; 
  $site_id = any2id('site', $siteObj_or_id);
  $search = ['site_id' => $site_id, 'parent_id' => $parent_id];
  if(isset($options['active']) && $options['active']) $search['active'] = 1; 
  if(isset($options['show_menu']) && $options['show_menu']) $search['show_menu'] = 1;
  
  $searchOptions['fields'] = ['id', 'parent_id', 'name as text', 'active', 'show_menu'];
  $tree = find_objects('site_page', $search, $searchOptions) ?: [];
  foreach($tree as $node) {
    $children = site_tree($site_id, $options, $node->id);
    $node->obj_type = $obj_type = 'site_page';
    $node->obj_id = $obj_id = $node->id;
    //$node->id = "{$obj_type}-{$obj_id}";
    $node->id = $obj_id;
    $node->child_count = $count = count($children);
    $node->icon = $count ? "" : "fa fa-file-o";
    $node->language = $lang;
    
    $auth_edit = 1;
    $auth_delete = $u_level == USER_LEVEL_SYSTEM || $node->user_id == $u_id ? 1 : 0;
    $node->auth = ["view" => 1, "edit" => $auth_edit, "delete" => $auth_delete];
    $classes = [];
    $classes[] = $node->active ? "bold" : "italic disabled";
    $classes[] = $node->show_menu ? "text-success" : "text-default";
    $node->li_attr = ["class" => implode(' ', $classes)];
    $node->children = $children;
  }
  return $tree;
  

  /** dummy root node 
  if($parent_id) return $tree; // not root
  $root = new stdClass;
  $root->text = get_object('site', $site_id, 'name');
  $root->child_count = count($tree);
  $root->icon = "fa fa-sitemap";
  $root->root = 1;
  $root->obj_type = $obj_type = 'site';
  $root->obj_id = $obj_id = $site_id;
  // $node->id = "{$obj_type}-{$obj_id}";
  $root->id = -1; 
  $root->active = 1;
  $root->children = $tree;
  */
  
  return $root;
}


// returns cache directory for site, page if given
function site_cache_dir($siteObj_or_id, $pageObj=NULL) {
  return clean_path($_SERVER['DOCUMENT_ROOT'].site_cache_path($siteObj_or_id));
}

// returns relative path to cache directory for site, page if given
function site_cache_path($siteObj_or_id, $pageObj=NULL) {
  $siteObj = any2obj('site', $siteObj_or_id);
  $result = "/sites/$siteObj->domain/cache/";
  return $pageObj ? clean_path($result.$pageObj->path) : $result; 
}

// helper function for spidering, used by site_spider_page and site_sitemap_html
function site_spider_node($siteObj_or_id, $node, $options=NULL) {
  //dump($tree);die();
  $siteObj = any2obj('site', $siteObj_or_id);
  $base_dir = site_cache_dir($siteObj);
  $path = $node->path;  
  $target_dir = clean_path($base_dir.$path);

  $start_time = getTime(); 
  $url = replace_query_var($node->url, '__cam', 1);
  print_log("Spidering node $name with url=$url");
  if($options['overwrite'] )$url = replace_query_var($url, '__overwrite', 1);
  list($html, $status) = get_html_and_status($url);      
  $end_time = getTime();
  $time = number_format(($end_time - $start_time),2);
  $len = strlen($html);
  print_log("Spidered node $name with status=$status len=$len");
  $message = $status == 200 ? 'OK' : "Error";
  $item = array('path' => $path, 'length' => bytes2human($len), 'time' => $time.'s', 'status' => $status, 'message' => $message);
  if($status == 200) {
    if(is_dir($target_dir) || mkdir($target_dir, 0775, true)) {
      $target_file = $target_dir.'index.html';
      if($dryrun) {
        echo("site_spider_node: (dryrun) Wrote $target_file ($len) to $target_dir<br>");
      } elseif(!write_file($target_file, $html)) {
        die("site_spider_node: Couldn't write $target_file to $target_dir");
      } else {
        //echo("Wrote $target_file ($len) to $target_dir<br>");
        //die();
      }
    } else {
      die("site_spider_node: Couldn't make $target_dir");
    }
  }   

  if($pb_id = $options['progress_id']) progressbar_increase_progress($pb_id);

  return $item;
}

function site_template_prepare($site_id, $source, $dest, $prepared = false) {
  
  if(!is_file($source)) return array(0, "$source does not exist");
  //if(!copy($source, $dest)) return array(0, "Could not copy template $source to $dest");
    
  $content = read_file($source);
  if(!$content) return array(0, "$source is an empty file or could not be read");

  $prepare = strpos($content, "{* Source:") === false;
  if(!$prepared && $prepare) {  /** don't replace if processed before */
    /** multiple passes needed as it will otherwise replace itself: { => {ldelim{rdelim} */
    $content = str_replace('}', '__§__', $content); // replace right curly bracket with tmp
    $content = str_replace('{', '{ldelim}', $content); // replace left curly bracket
    $content = str_replace('__§__', '{rdelim}', $content); // replace right curly bracket using tmp
    $content = str_replace('"assets/', '"/assets/', $content); // replace asset path
    $content = template_replace_images($site_id, $content);
  }
  
  /** Add comment */
  $now = now();
  $content = "{* Source: $source Target: $dest Created: $now *}\n".$content;

  
  //echo("content = $content");
  if(!write_file($dest, $content)) return array(0, "Could not write template to $dest");
  return array(1, "");
  
}

function template_replace_images($site_id, $content) {
  /** Replace image tags with content tags */
  $pattern = '|\<img\s(.*)\>|i'; // case insensitive

  $output = preg_replace_callback (
    $pattern, 
    function($matches) {
      //dump($matches);
      $match = $matches[1];
      if(!$match) return '';

      $match = trim(trim($match, "/"));
      $attrs = explode(' ', $match);
      
      $tagObj = new stdClass;
      foreach($attrs as $attr) {
        $attr = trim($attr);
        //$value = strpos($value, '"') === 0 ? trim($value, '"') : trim($value, "'"); /** strip single or double quotes */          
        list($key,$value) = explode('=', $attr);
        $key = trim($key);
        $value = trim($value);
        $value = trim($value, "\"'");
        // $value = str_replace('"', '\"', $value); // escape quotes (json_encode does this)
        //echo("Key=$key value=$value<br>");
        if($key == 'src') { /** check that image exists and get dimensions */
          $src = $value;
        } else {
          $tagObj->$key = $value;
        }
        // {{"name": "welcome-image", "type":"image", "value": "/assets/images/demo/desktop.png", "resize": 640, "class": "img-responsive animate_fade_in", "style": "opacity: 1; right: 0px;"}}
        // Tag = {{"class":"img-responsive","alt":"","name":"image-assetsimagesdemobrands8.jpg-940","type":"image"}}          
      }
      if($src) {
        $tagObj->name = "image-".url_safe($src)."-".rand(1,1000);
        $tagObj->type = "image";
        
        $h = $tagObj->height ?: 0;
        $w = $tagObj->width ?: 0;
        $max_explicit = ($h || $w) ? max($h, $w) : 0; 

        $filename = is_url($src) ? $src : siteUrl(false).$src;
        
        $tagObj->value = $filename;
        
        $imageInfo = getimagesize($filename);
        if(!$imageInfo) return $match." {* $filename is not an image *}\n";
        $width = $imageInfo[0];
        $height = $imageInfo[0];
        $max = max($width, $height);
        
        $max = $max_explicit ?: $max;
        if($max) $tagObj->resize = $max;
        
        $tag = "{".json_encode($tagObj)."}";

        //echo("Tag = $tag<br>");
      } else {
        //echo("No src, no tag".dump($tagObj, true));
        return $match." {* Failed to parse image tag *}\n";
      }
      //echo(html_break());
      return $tag;
    }, 
    $content);
  return $output;
}

 
// apply controller, parse template, return output
// template is set in pageObj->template
// controller is set in pageObj->controller
function fetch_template($siteObj, $pageObj, $options = array()) {

  if(!$pageObj->controller && $options['controller']) $pageObj->controller = $options['controller'];
  if(!$pageObj->template && $options['template']) $pageObj->template = $options['template'];

  $scope = $options['scope'];
  $template = $pageObj->template;
  if(!$template) return "fetch_template: Missing template";

  //if(in_array($template, ['_rental-list.html', '_rental-list-item.html'])) timer('property-search', "fetch-template {$template} start");        
  
  if(!$pageObj->controller) $pageObj->controller = 'generic';
  
  $pageObj = apply_controller($siteObj, $pageObj, array("template" => $template, "scope" => $scope));
  
  
  //timer('property-search', "fetched-template {$tpl}");        

  $filename = smarty_preparse_template($template);
  
  $output = smarty_parse_template($siteObj, $pageObj, $filename);

  //if(in_array($template, ['_rental-list.html', '_rental-list-item.html'])) timer('property-search', "fetch-template {$template} done");        
  
  return $output;
}


// apply controller if any and return scope in pageObj
function apply_controller($siteObj, $pageObj, $options = array()) {
  $scope = new StdClass;
    
  $tpl = $pageObj->template;
  $ctrl = $pageObj->controller;
  $name = $pageObj->name;
  
  // global controller
  $controller_func = $pageObj->controller ? "controller_".$pageObj->controller : 'controller_'.url_safe($pageObj->name);
  if(function_exists($controller_func)) {
    $scope = call_user_func($controller_func, $siteObj, $pageObj, $options);  
    $pageObj->scope = $scope;
    $scope->global_controller = str_replace("controller_", '', $controller_func);
  }
  
  // site controller
  if($lib_prefix = $siteObj->library_prefix ?: $siteObj->shortname) {
    $controller_func = $pageObj->controller ? $lib_prefix."_controller_".$pageObj->controller : $lib_prefix.'_controller_'.url_safe($pageObj->name);
    if(function_exists($controller_func)) {
      $scope = call_user_func($controller_func, $siteObj, $pageObj, $options);
      $scope->site_controller = str_replace($lib_prefix."_controller_", '', $controller_func);    
    }
  }
  
  if($global = $_SESSION['global_scope']) {
    $scope = object_extend($scope, $global);
  }

  if(!isset($scope->controller)) $scope->controller = $scope->site_controller ?: $scope->global_controller;
  if(!isset($scope->template)) $scope->template = $pageObj->template;
  
  $pageObj->scope = $scope;
  $_SESSION['scope'] = $scope;
  
  $page_overrides = array('template', 'template_id', 'http_code'); // page vars that can be ovverriden by scope
  foreach($page_overrides as $f) if(isset($scope->$f)) $pageObj->$f = $scope->$f;
      
  return $pageObj;
}
  

function site_parse_template($siteObj, $pageObj, $template, $options = array()) {
  global $__LIVE,$__LOCAL_TEMPLATE,$__TEMPLATE;
  $auth_edit = $options['can_edit'] ?: $options['auth_edit'];

  //$pattern = '|\<!--\s?\{(.*?)\}\s?--\>|'; // ungreedy to allow more on one line
  // $pattern = '|\{\{\s?(.*?)\s?\}\}|'; // ungreedy to allow more on one line
  $pattern = '|\{\{\s?(.*?)\s?\}\}|s'; // ungreedy to allow more on one line
  
  $output = preg_replace_callback (
      $pattern, 
      function($matches) {
        //dump($matches);
        $match = $matches[1];
        if(!$match) return '';
        if($match[0] == '"' || $match[0] == "'" || $match[0] == "[") { // json?
          return parse_template_json($match);
        } else if($match[0] == '$') { // variable
          return parse_template_variable($match);
        } else { // no match.
          return ' { '.$match.' } ';
        }
      }, 
      $template);
  $debug = '';
  //if(!$__LIVE) $debug = "tmp: {$__TEMPLATE} local:{$__LOCAL_TEMPLATE}<br>";
  return $debug.$output;
}


function smarty_template($siteObj, $pageObj, $filename, $options = array()) {
  $tpl_filename = smarty_preparse_template($filename); // parse our own template structure, write smarty template
  if(!$tpl_filename) die("smarty_template: preparse $filename returned null - template=$template");
  $output = smarty_parse_template($siteObj, $pageObj, $tpl_filename, $options); // now run in through smarty for further parsing      
  return $output;
}

// look for page template in file, return smarty template filename
function site_page_template($siteObj, $pageObj, $options = array()) {
  $template = '';
  $parse = isset($options['parse']) ? $options['parse'] : true; 
  
  $page_name = $pageObj->name;
  $filename = pick_first($options['template'], $pageObj->template, strtolower($page_name));
  if(!strpos($filename, ".html")) $filename .= ".html";

  $pageElementArray = array(); // global

  // read page elements from database, store in session
  $template['$title'] = $pageObj->title;
  $template['$content'] = $pageObj->content;
  if($pageElementObjs = find_objects('page_element', array('site_id' => $siteObj->id, 'page_id' => $pageObj->id, 'language' =>  [$pageObj->language, '*']))) {
  //if($pageElementObjs = find_objects('page_element', array('site_id' => $siteObj->id, 'page_id' => $pageObj->id, 'language' =>  $pageObj->language))) {
    foreach($pageElementObjs as $pageElementObj) {
      $pageElementArray[$pageElementObj->name] = $pageElementObj;
      $template[$pageElementObj->name] = $pageElementObj->content;
    }
  }
  
  //return dump($template,true).dump($pageObj,true);
  
  //echo("site_page_template: page elements=".dump($pageElementArray, true));
  $_SESSION['page_elements'] = $pageElementArray;  
  $_SESSION['page_template'] = $template;  

  $tpl_filename = smarty_preparse_template($filename, $options); // parse our own template structure, write smarty template
  
  if($parse && !$tpl_filename) return "";
  if(!$parse) {
    if(!$tpl_filename) die("site_page_template: no template for $filename");
    return $tpl_filename;
  }
  
  /** old */ 
    
  $template = smarty_parse_template($siteObj, $pageObj, $filename, $options); // now run in through smarty for further parsing    

  $show_title = $options['show_title'];
  $title_group = $show_title ? site_content_title_group($siteObj, $pageObj, $options) : '';
  return $title_group.$template;
}


// takes our own template file, parses it, writes a smarty template and returns filename if successful
function smarty_preparse_template($filename, $options = array()) {  
  global $__LOCAL_TEMPLATE, $__TEMPLATE, $__TEMPLATE_PATH;
  $docroot = $_SERVER['DOCUMENT_ROOT']."/";
  $approot = $_SESSION['app_root'];
  $smarty_dir = $docroot.'smarty/templates';
  if(!strpos($filename, '.html')) $filename .= ".html";
  if(0 && $_SESSION['live'] && file_exists("$smarty_dir/$filename")) { // for www, no preparsing, use already parsed smarty template
    return "$smarty_dir/$filename";
  }
  
  $__LOCAL_TEMPLATE = 0;
  
  $site_template_file = $docroot."pages/$filename";
  $app_template_file = "$approot/pages/$filename";
  if(file_exists($site_template_file)) {
    $__LOCAL_TEMPLATE = 1;
    $template_file = $site_template_file;
  } else if(file_exists($app_template_file)) {
    $template_file = $app_template_file;
  } else {
    //die("$filename not found in $site_template_file or $app_template_file");
    return ''; // no template
  }
  $__TEMPLATE = $filename;
  $__TEMPLATE_PATH = $template_file;

  if($raw_template = read_file($template_file)) {
    //echo("read ".strlen($raw_template)." from $template_file<br>");
    $now = now();
    $options['context'] = $template_file;
    
    //echo(" parsing $template_file<br>");
    $parsed_template = "{* automatically generated on $now from $template_file. DO NOT EDIT *}".PHP_EOL.
      site_parse_template($siteObj, $pageObj, $raw_template, $options).PHP_EOL;
      
    //$parsed_template = str_replace(array('{', '}'), array('{ldelim}','{ldelim}'), $parsed_template); // otherwise smarty crahses
    $smarty_template = $docroot."smarty/templates/$filename";
    $path_parts = pathinfo($smarty_template);
    $dir = $path_parts['dirname']."/";
    //$dir = "/websites/test.hitabrick.com/smarty/templates/foo/bar/";
    //$dir = "/websites/test.hitabrick.com/smarty/templates/template/traveler/";
    if(!is_dir($dir) && !mkdir($dir, 0775, true)) die("smarty_preparse_template: Failed to create $dir");
    if(!write_file($smarty_template, $parsed_template)) die("smarty_preparse_template: Failed to write to ".$docroot."smarty/templates/$filename");     
    //echo("wrote ".strlen($parsed_template)." to $smarty_template<br>");
    return $filename;
  }
}

// options is used to pass extra data to scope
function smarty_parse_template($siteObj, $pageObj, $filename, $options = array()) {
  //mydie(dump($siteObj, true).caller_stack());
  global $__LANGUAGE, $__LANGUAGES, $__USER, $__USER_LEVEL, $__USER_ID, $__PATH_VAR,$__EDIT_MODE, $__CLIENT_ID;
  global $u_id, $u_level;
  
  if (!class_exists('Smarty')) {
    require_once('Smarty/Smarty.class.php');    
  }
  $root = $options['root']; // top level page template? - not in use
  $main = $options['main']; // main template (content)
  
  $global = $_SESSION['global_scope'] ?: array();
  
  $docroot = rtrim($_SERVER['DOCUMENT_ROOT'], '/');
  $userObj = $_SESSION['userObj'];

  $query_string = get_query_string();
  $this_path = this_path();
  
  if($query_string) $query_string = "?$query_string"; // so we can append it to URLs in template

  $auth_edit = $_SESSION['auth_edit'];
  if($scope = $options['scope'] ?: $pageObj->scope) {
    unset($options['scope']);
    //echo("scope set=".dump($scope, true));
  } else {
    $scope = $_SESSION['scope'] ?: new stdClass;
  }
  
  if(is_array($options)) foreach($options as $k => $v) $scope->$k = $v;
  //dump($scope);die();
  $scopeAr = is_array($scope) ? $scope : obj2array($scope, true); // recursive
  $globalAr = obj2array($global);

  $template = $_SESSION['page_template'];
  $template_dir = $docroot.'pages';
  
  $smarty = new Smarty();

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

  $smarty->assign('dump', smarty_dump);

  try {                
    $template = $smarty->fetch($filename);
  }
    catch (Exception $e) {
    $smarty_error = $e->getMessage();
    $scope->error = htmlentities($smarty_error);
    $template = "Cannot parse $filename:<br><br>{$smarty_error}";
  }

  //$template = $smarty->fetch($filename);

  //dump($userObj);die();
  
  $_SESSION['scope'] = NULL;
  $output =  '';
  
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
      if(1) { /** todo: test if printed in template */
        //$output .= form_text('foo', $template);
        $output .= print_alert($error, "error");
      }
    }
  }
  
  return $output.$template;
}

function smarty_case($scase) {
  switch(strtolower($scase)) {
    case 'u': 
      $case = UPPERCASE;
      break;
    case 'l': 
      $case = LOWERCASE;
      break;
    case 'c': 
      $case = CAPITALIZE;
      break;
    case 't': 
      $case = TITLECASE;
      break;
    default:  
      $case = -1;
      break;
  }
  return $case;
}

// this translates and replaces: accepts a varying number of arguents after $term and $scase, which are passed to phrase. No options accepted
function smarty_transplace($term, $scase='') {
  $args = func_get_args();
  $args[1] = smarty_case($scase);
  $phrase = call_user_func_array('phrase', $args);
  return $phrase;
}

// set case to ne or editable to 0 to prevent in-line editable 
function smarty_translate($term, $scase = '', $editable=1) {
  global $__LANG, $__SITE, $__LOCAL_TEMPLATE;
  print_log("smarty_translate: $term ($__LANG) $case", 'dictionary', LOG_LEVEL_TEST);
  $case = smarty_case($scase);
  $options = [];
  if($__LOCAL_TEMPLATE) $options['site_id'] = $__SITE->id;
  $phrase = phrase($term, $case, $options);

  global $u_level;

  $auth_edit = $u_level >= USER_LEVEL_STAFF;
  if($scase == 'ne') $editable = 0;
  if($auth_edit && $_SESSION['__edit_mode'] && $editable) { 
    global $__PAGE;
    $term = strtolower(trim(str_replace(' ', '_', $term)));
    $dic_id = find_object('dictionary', ['term' => $term, 'language' => $__LANG], 'id');
    print_log("smarty_translate: edit $term ($__LANG) id: $dic_id", 'dictionary', LOG_LEVEL_TEST);
    
    if($dic_id) {
      $id = site_edit_id($__SITE, $__PAGE, $auth_edit, 'dictionary', 'phrase', $dic_id, array('type' => 'text'));
      $edit_options = array('id' => $id);
      $phrase = html_span($phrase, '__edit __dic', $edit_options); // allow edit
    }
  }
  return $phrase;
}

function smarty_dump($obj) {
  return dump($obj, true);
}

function smarty_find_object($obj_type, $search, $field='') {
  $search = json_decode($search, true);
  $result = find_object($obj_type, $search, $field);
  return is_object($result) ? (array) $result : $result;
}

function smarty_find_objects($obj_type, $search, $options=[]) {
  if(!is_array($search)) $search = json_decode($search, true);
  $result = find_objects($obj_type, $search, $options);
  return $result;
}
function smarty_get_object($id, $obj_type, $field='') {
  $result = get_object($obj_type, $id, $field);
  return is_object($result) ? (array) $result : $result;
}

function smarty_property_geolink($obj_or_id, $path = '') {
  $siteObj = $_SESSION['siteObj'];
  $obj = any2obj('property', $obj_or_id);

  if(!$path && is_property_type($obj->type)) $path = site_page_link($siteObj, property_type2page($obj->type));

  //if(!$path) $path = site_page_link($_SESSION['siteObj'], $siteObj->property_type);
  //echo("Path:$path t={$siteObj->property_type}");

  return property_geolink($obj, $path);
}
  
// set page to make non-db lookup
function smarty_property_link($obj_or_id, $path = '') {
  return smarty_property_geolink($obj_or_id, $path);
  
  /**
  $siteObj = $_SESSION['siteObj'];
  $obj = any2obj('property', $obj_or_id);

  $slugged_name = slugify($obj->name);
  $slug = "{$slugged_name}~{$obj->id}";
  if(!$page) $page = site_page_link($siteObj, property_type2page($obj->type));
  return "{$page}{$slug}";
  return $page && $slug ? $geodir.$page.$slug."/" : "#";
  */
}

function smarty_editor($id, $options = array()) {
  $pageElement = get_object('page_element', $id);
  $val = $pageElement->content;
  $fld = "page_element-$id";
  
  
  $editor = form_text('content', $val, array("class" => "summernote form-control special", "data-height" => $fck_h, "data-full" => 1));
  $hidden = form_input("obj_type", "hidden", "page_element");
  $hidden .= form_input("id", "hidden", $id);
  $submit = form_input("submit", "submit", "Save", array("class" => "btn btn-success"));
  $form = html_form($hidden.$editor.$submit, "form-".$fld, '', 'post', 'ajax-submit', array('data-handler' => 'save'));
  return $form;
}

function smarty_uploader($obj_type, $id, $options = array()) {
  global $u_id;
  $field = isset($options['field']) ? $options['field'] : 'media'; /** todo: look at class def, pick fist media type */
  
  $output = "Uploader for media $obj_type $id";
  
  if($options && !is_array($options)) $options = json_decode($options, true); /** we now use json in attribute definition */ 

  $output .= dump($options, true);

  
  //die("smarty_uploader obj_type=$obj_type id=$id".caller_stack());
  $obj = get_object($obj_type, $id);
  if(!$obj) return print_errors("$obj_type $id not found");
  
  //return "Uploader media $id".dump($options, true);
  $resize = $options['resize'] ?: 0;
  
  $upload_options = array("resize" => 1);  
  $upload_options = array_extend($upload_options, $options);

  $upload_options['allow_multiple'] = 1; /** disable for now */
  
  //$upload_options['minimum_size'] = array(1080, 1920); // either short side >= 1080 or long side >= 1920
  $val = $id;
     
  $mediaData['user_id'] = $u_id;
  $mediaData['parent_id'] = $parent_id = $id;
  $mediaData['parent_type'] = $parent_type = $obj_type;
  $mediaData['parent_field'] = $fld = $field;
  //$mediaData['name'] = $mediaObj->name;
  
  $upload_options['download_template'] = $options['download_template'] ?: "";
  
  $upload_options['media_data'] = $mediaData;
  $upload_options['data-value_list'] = $val;
  $upload_options['show_file_list'] = false;
  $upload_options['title'] = "Click or drag to upload media";
  $upload_options['resize'] = $resize; /** resize to max px longest side ? */
  
  $handler = isset($options['handler']) ? $options['handler'] : '';
  if($upload_options['handler'] = $handler) {
    $handler_options = array();
    $upload_options['handler_options'] = $handler_options;
  }

  $uploader = jquery_file_uploader("$parent_type-$parent_id-$fld", $val, $upload_options);
  
  $output = $uploader;
  return $output;
}

// media uploader
function smarty_media_uploader($id, $options = array()) {
  global $u_id;
  $output = "Media Uploader for media $id";
  if($options && !is_array($options)) $options = json_decode($options, true); /** we now use json in attribute definition */ 

  $output .= dump($options, true);
  
  $mediaObj = get_object('media', $id);
  if(!$mediaObj) return print_errors("Media $id not found");
  
  //return "Uploader media $id".dump($options, true);
  $resize = $options['resize'] ?: 0;
  
  $upload_options = array("resize" => 1);  
  $upload_options = array_extend($upload_options, $options);
  $upload_options['allow_multiple'] = 0; /** disable for now */
  
  //$upload_options['minimum_size'] = array(1080, 1920); // either short side >= 1080 or long side >= 1920
  $val = $id;
     
  $mediaData['user_id'] = $u_id;
  $mediaData['parent_id'] = $parent_id = $mediaObj->parent_id;
  $mediaData['parent_type'] = $parent_type = $mediaObj->parent_type;
  $mediaData['parent_field'] = $fld = $mediaObj->parent_field;
  $mediaData['name'] = $mediaObj->name;
  
  $upload_options['download_template'] = $options['download_template'] ?: "";
  
  $upload_options['media_data'] = $mediaData;
  $upload_options['data-value_list'] = $val;
  $upload_options['show_file_list'] = false;
  $upload_options['title'] = "Click or drag to upload profile image";
  $upload_options['resize'] = $resize; /** resize to max px longest side ? */
  
  $handler = isset($options['handler']) ? $options['handler'] : '';
  if($upload_options['handler'] = $handler) {
    $handler_options = array();
    $upload_options['handler_options'] = $handler_options;
  }

  $uploader = jquery_file_uploader("$parent_type-$parent_id-$fld", $val, $upload_options);
  
  $output = $uploader;
  return $output;
}


function smarty_editable($val, $obj_type, $obj_id, $field = '', $options = []) {
  global $__SITE, $__PAGE, $__AUTH_EDIT, $__EDIT_MODE;
  
  /** debug
  if(!$__AUTH_EDIT) return "no global auth edit";
  if(!$__EDIT_MODE) return "not edit mode";
  $auth_edit = auth_action($obj_type, 'edit', $obj_id);
  if(!$auth_edit) return "no auth edit $obj_type $obj_id";
  */
  
  if(!$__AUTH_EDIT || !$__EDIT_MODE) return $val;
  
  $auth_edit = auth_action($obj_type, 'edit', $obj_id);
  if(!$auth_edit) return $val;
  
  // $type = isset($option['type']) ? $option['type'] : ''; // class_edit_type($obj_type, $field);  // todo: class type  
  // $id = site_edit_id($__SITE, $__PAGE, $auth_edit, $obj_type, $field, $id, array('type' => $type ?: 'text'));
  $id = site_edit_id($__SITE, $__PAGE, $auth_edit, $obj_type, $field, $obj_id);
  return html_section($val, '__edit', ['id' => $id]);
}
  
// implements function in smarty template that allows editing of variables:
// {editable var="page.title"}
function smarty_edit($attrs) {
  $pageObj = $_SESSION['pageObj'];
  $siteObj = $_SESSION['siteObj'];
  //$pageElementArray = $_SESSION['page_elements'];  

  $auth_edit = $_SESSION['auth_edit'];
  list($obj_type, $field) = explode(".", $attrs['var']);

  if(!in_array($obj_type, array("page", "page_content", "site"/*, "page_element"*/))) return "smarty_edit error: unsupported object type $obj_type";
  if($obj_type == 'page') $obj_type = 'page_content';

  $class_def = get_class_def($obj_type, false);  
  $attr = $class_def->fields[$field];
  if(!$attr) return "smarty_edit error: $obj_type has no field $field";

  $type = $attr[ATT_TYPE];
  if($type == 'str') $type = 'text';

  switch($obj_type) {
  case "page_content":
    $value = $pageObj->$field;
    $edit_id = $pageObj->content_id;
    break;
  case "site":
    $value = $siteObj->$field;
    $edit_id = $siteObj->id;
    break;
  }
  if(!$_SESSION['__edit_mode']) return $value;      

  $edit_class = '__edit '; 
  $media_button = '';
  if(in_array($type, array('image','audio','video', 'media'))) {
    $media_button = html_div(html_image("/images/icons/".$type.".png", 'edit'), 'ie_edit_link');
    $safe_name = url_safe($name);
    $page_id = $pageObj->id; // name might change, so use ID
    $media_options['path'] = "/user/page/$page_id/$safe_name/"; 
    $media_options['allow_multiple'] = false;
    $media_button = "smarty_edit media: Edit $type";
    return $media_buttons;
  }
  $id = site_edit_id($siteObj, $pageObj, $auth_edit, $obj_type, $field, $edit_id, array('type' => $type));
  $edit_options = array('id' => $id);
  
  if($media_options) {
    $class_options->$field = array(ATT_OPTIONS => $media_options); // override options of field content
  }
  $output = html_section($value.$media_button, '__edit', $edit_options);
  return $output;
  
  //echo("Smarty edit ot=$obj_type fld=$field");
}

    
// template parsing functions
function parse_template_json($match) { 
  global $auth_edit, $u_id;
  $json = $match[0] == '[' ? '["'.str_replace('"', '\"', substr($match, 1, -1)).'"]' : "{".$match."}"; // turn back into json array or object
  $json = str_replace("\n", '', $json);
  $data = json_decode($json);

  if(!$data) {
    return ''; // todo: show error
  }
  
  $siteObj = $_SESSION['siteObj'];
  $pageObj = $_SESSION['pageObj'];
  $pageElementArray = $_SESSION['page_elements'];  
  
  if(is_array($data) && count($data)) { // this allows simplified tags for page_elements {{[ and ]}}
    //echo("data is array".dump($data, true));
    $value = $data[0]; // remove [ and ]
    $data = new stdClass;
    
    $rand = hash('adler32', $value);
    $data->name = "pe-$rand";
    $data->type = $type = strip_tags($value) == $value ? "text" : "html"; // if strip_tags == str, text, else html
    $data->value = $value;
    //echo("data is now obj".dump($data, true));
    //die();
    
  } else if($filename = $data->extend) { // include file to be parsed
    //echo(" found include $filename, calling preparse...<br>");
    unset($data->extend);
    if($tpl_filename = smarty_preparse_template($filename)) {
      return "{extends file=\"$tpl_filename\"}";
    }
    die("parse_template_json: preparse extend file $tpl_filename returned null");
  } else if($filename = $data->include) { // include file to be parsed
    //echo(" found include $filename, calling preparse...<br>");
    unset($data->include);
    $data_str = array2args($data);
    if($tpl_filename = smarty_preparse_template($filename)) {
      return "{include file=\"$tpl_filename\" $data_str}";
    }
    die("parse_template_json: preparse include file {$filename} returned null");
  }
  
  $debug = '';
  $name = $data->name;
  $dbObj = $pageElementArray[$name];
  $type = $data->type;
  $value = $dbObj ? $dbObj->content : $data->value;
  $options = $data->options ? (array) $data->options : array();
  $element_id = $dbObj->id;
  
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
      //$debug = dump($mediaData, true);
      if(1) {      
        print_log("parse_template_json: resize=".dump($mediaData['resize'], true), 'resize', LOG_LEVEL_TEST);
        list($media_id, $media_errors) = add_object('media', $mediaData);
        if($media_id) update_object('page_element', array('media' => $media_id), $dbObj->id);
        else if($media_errors) $debug = print_errors($media_errors);
      }
    }
    $media_src = $media_id ? print_media($media_id, array('source_only' => true)) : $value;
    //$media_src = $media_id ? print_media($media_id, array('source_only' => true)) : $value;
  }

  $obj_type = 'page_element'; // default  for page_element
  $edit_id = $dbObj->id; // default for page_element
  
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
    //$output .= dump($dbObj, true);
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

  if($store && !$pageElementArray[$name]) { // store in database if doesn't exist
    $db_data = array();
    $db_data['site_id'] = $siteObj->id;
    $db_data['page_id'] = $pageObj->id;
    $db_data['language'] = $pageObj->language;
    $db_data['name'] = $name;
    $db_data['type'] = $type;
    $db_data['content'] = $value;
    $db_data['options'] = $options ? json_encode($options) : '';
    //dump($db_data);
    //echo("
    list($id, $errors) = add_object('page_element', $db_data);
    if($errors) {dump($db_data);dump($errors);die();}
    $edit_id = $id;
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

// template parsing functions
function parse_template_variable($match) {
  $pattern = '#\$(page|site|template|user|scope)\.([a-zA-Z_\-0-9]+)\.?([a-zA-Z_\-0-9]+)?\.?([a-zA-Z_\-0-9]+)?\.?([a-zA-Z_\-0-9]+)?#';
  if(preg_match($pattern, $match, $m)) {
    $var = $m[1];
    $key = $m[2];
    if($var && $key) {
      switch($var) {
      case 'site':
        $siteObj = $_SESSION['siteObj'];
        return $siteObj->$key;
        break;
      case 'page':
         $pageObj = $_SESSION['pageObj'];
         return $pageObj->$key;
        break;
      case 'template':
        $pageElementArray = $_SESSION['page_elements'];  
        $pageElementObj = $pageElementArray[$key];
        return $pageElementObj->content;
        
      case 'user':
        $userObj = $_SESSION['userObj'];
        return $userObj->$key;
    
      case 'scope':
        $count = count($m);
        $scope = $_SESSION['scope'];
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


// move everything from one site to another
function move_site_content($from_site, $to_site, $options = array()) {
  $execute = $options['execute'];
  $classes = get_classes();
  $count = count($classes);
  echo("There are $count classes<br>");
  //dump($classes);die();
  $classAr = array();
  foreach($classes as $class) {
    $obj_type = $class->type;
    $fields = class_fields($obj_type, false);
    if(in_array('site_id', $fields)) {
      $classAr[] = $obj_type;
    }
  }
  $count = count($classAr);  
  echo("There are $count classes with site_id<br>");
  $rows = array();
  $rows[] = array("obj_type", "table", "count");
  foreach($classAr as $obj_type) {
    $table = get_object_table($obj_type);
    $count = db_getOne("SELECT count(*) from $table WHERE site_id=$from_site");
    if($count) {
      $rows[] = array($obj_type, $table, $count);
      if($execute) db_query("UPDATE $table SET site_id=$to_site WHERE site_id=$from_site");
    }
  }
  $output = html_table($rows, array('class' => 'web20'));
  return $output;
}

// exports all content needed for a site to live on a another database (sql file)
// todo: figure out which address to export;

function export_site_content($site_id, $options = array()) {
  $siteObj = get_object('site', $site_id);
  $client_id = $siteObj->client_id;  
  $clientObj = get_object('client', $siteObj->client_id);
  $legal_id = $siteObj->legal_entity_id;
  $legalObj = get_object('legal_entity', $siteObj->legal_entity_id);

  
  $exportAll = array('address_type','article_type','countries','currency', 'language', 'property_type', 'description_type','media_type','mime_type','page_type','phone_type','provider','provider_key','security','site_template','user_level','user_role', 'mail_queue_seq');   
  
  $export['all'] = $exportAll;   // export structure + all data
  $export['where'] = array();    // export structure + data matching WHERE condition
  $export['struct'] = array();   // export structure only

  
  $execute = $options['execute'];
  $classes = get_classes();
  $count = count($classes);
  
  $property_site = $siteObj->show_types; // todo check
  $payment_site = $siteObj->payment_options;
  $user_site = $siteObj->allow_user_login || $siteObj->allow_user_register;
  $gallery_site = $siteObj->gallery_site;
  
  
  $property_tables = array();
  $payment_tables = array();
  
  //echo("There are $count classes<br>"); 
  //dump($classes);die();
  $classAr = array();
  foreach($classes as $classObj) {    
    $obj_type = $classObj->type;
    $table = $classObj->table;
    $group = $classObj->group;
    if(!$property_site && in_array($group, array('event', 'property', 'enquiry', 'location', 'property-user', 'property-content'))) continue;
    if(!$user_site && $group == 'user') continue;
    if(!$payment_site && in_array($group, array('accounting', 'product'))) continue;
    // if(!$gallery_site && $group == 'gallery') continue; (we need these for image upload)
    if(!$pet_site && $group == 'pet') continue;
    if(!$golf_site && $group == 'golf') continue;
    if(!$social_site && $group == 'social') continue;
    if(!$content_site && $group == 'content') continue;
    

    $fields = class_fields($obj_type, false);

    $classObj->has_site   = $has_site   = in_array('site_id', $fields);
    $classObj->has_client = $has_client = in_array('client_id', $fields); 
    $classObj->has_legal  = $has_legal  = in_array('legal_entity_id', $fields);

    $classObj->site_count = $classObj->has_site ? db_getOne("SELECT count(*) from $table WHERE site_id=$site_id") : -1;    
    $classObj->client_count = $classObj->has_client ? db_getOne("SELECT count(*) from $table WHERE client_id=$client_id") : -1;
    $classObj->legal_count  = $classObj->has_legal  ? db_getOne("SELECT count(*) from $table WHERE legal_entity_id=$legal_id") : -1;
    
    $where = "";
    if($obj_type == 'site') {
      $has_site = true;
      $where = "id=$site_id";
      $classObj->site_count = db_getOne("SELECT count(*) from $table WHERE $where") ?: -1;
    } else if($obj_type == 'client') {
      $has_client = true;
      $where = "id=$client_id";
      $classObj->client_count = db_getOne("SELECT count(*) from $table WHERE $where") ?: -1;
    } else if($obj_type == 'legal_entity') {
      $has_legal = true;
      $where = "id=$legal_id";
      $classObj->legal_count = db_getOne("SELECT count(*) from $table WHERE $where") ?: -1;      
    }
    
    if($has_site || $has_client || $has_legal) {
      if(!$where) {
        if($classObj->site_count > 0) $where = "site_id=$site_id"; 
        else if($classObj->client_count > 0) $where = "client_id=$client_id"; 
        else if($classObj->legal_count > 0) $where = "legal_entity_id=$legal_id"; 
      }
      if($obj_type == 'user') $where = $where ? "$where OR id=501" : "id=501"; // add system user
      if($where) {
        $export['where'][$table] = $where;
      } else {
        $export['struct'][] = $table;
      }
      $classAr[] = $classObj;      
    }
    $all_tables = array_merge($exportAll, array_keys($export['where']), $export['struct']);
    $table_list = quoted_list($all_tables);
    $struct_table_list = quoted_list($export['struct']);
    $export['where']['db_sequence'] = "seq_name IN ($table_list)";
  }

  $address_ids = array($siteObj->address_id, $legalObj->address_id, $clientObj->address_id, 44);
  if($user_aids = find_objects('user', array('site_id' => $site_id), array('field' => 'address_id'))) {
    $address_ids = array_merge($address_ids, $user_aids);
  }
  $address_id_list = implode(',', $address_ids);
  $export['where']['address'] = "id IN ($address_id_list)";
  $export['where']['site_scheme'] = "id=$siteObj->scheme_id";
  $export['where']['site_config'] = "id=$siteObj->config_id";
  $export['where']['site_dim'] = "id=$siteObj->dim_id";
  $export['where']['property_config'] = "id=$siteObj->property_config_id";
  if(!$export['where']['site_content']) $export['struct'][] = 'site_content';
  
  // 'db_sequence', where seq_name in ();
  
  $count = count($classAr);  
  // echo("There are $count classes with site_id, client_id, or legal_entity_id<br>");
  //dump($classAr);exit;
  $rows = array();
  $rows[] = array("obj_type", "group", "table", "site", "client", "legal");
  foreach($classAr as $classObj) {
    $site_count   = $classObj->site_count > -1   ?  $classObj->site_count   : html_span("x", 'red');    
    $client_count = $classObj->client_count > -1 ?  $classObj->client_count : html_span("x", 'red');
    $legal_count  = $classObj->legal_count > -1  ?  $classObj->legal_count  : html_span("x", 'red');    
    $rows[] = array($classObj->type, $classObj->group, $classObj->table, $site_count, $client_count, $legal_count);
  }
  $output = html_table($rows, array('class' => 'web20'));

  $domain = $siteObj->domain;
  $base_dir = is_dir("/websites/test.$domain/db/dump") ? "/websites/test.$domain/db/dump" : "/backup/db/dump"; 

  $sql_export_filename = "$base_dir/export-site-".$siteObj->shortname."-".date('Ymd').".sql";
  $sql_export_file = '';
  $cmds = array();
  foreach($export['all'] as $table) $cmds[] = "mysqldump --user=apt --password=killa113 --compact --add-drop-table aptdb_v14 $table >> $sql_export_filename";
  foreach($export['struct'] as $table) $cmds[] = "mysqldump --user=apt --password=killa113 --compact --add-drop-table aptdb_v14 --no-data $table >> $sql_export_filename";
  foreach($export['where'] as $table => $where) $cmds[] = "mysqldump --user=apt --password=killa113 --compact --add-drop-table  aptdb_v14 $table --where=\"$where\" >> $sql_export_filename";
  
  $result = '';  
  
  if(is_file($sql_export_filename)) unlink($sql_export_filename);
  foreach($cmds as $cmd) {
    $result .= execRootCmd($cmd, $cmd_output, $return_var);
  }
  $shortname = $siteObj->shortname;
  
  $sql_import_filename = "$base_dir/import-site-$shortname-".date('Ymd').".sql";

  $sql_import_file = "source $sql_export_filename;\n";
  $sql_import_file .= "UPDATE db_sequence SET nextid=1000 WHERE seq_name in ($struct_table_list);\n";
  $len = write_file($sql_import_filename, $sql_import_file);
  if($len) {
    $output .= "OK, wrote $len to $sql_import_filename<br>";
  } else {
    $output .= "Error, failed to write to $sql_import_filename<br>";
  }

  if(is_file("$base_dir/../import-site-$shortname.sql")) unlink("$base_dir/../import-site-$shortname.sql");
  $cmd = "ln -s $sql_import_filename $base_dir/../import-site-$shortname.sql";  
  execRootCmd($cmd, $cmd_output, $return_var);
  $cmds[] = $cmd;
  if($options['debug']) {
    $cmd_str = dump($cmds,true);
    $output .= form_text('cmds', $cmd_str);
    $output .= form_text('result', $result);
  }
  
  return $output;
}

function controller_error($error, $status = 400, $options = []) {
  $scope = new stdClass;
  $scope->error = $error;
  $scope->template = $status;
  
  return $scope;
}

function search_result($siteObj, $obj_type, $term, $search_fields, $id_field, $options = array()) {
  $scope = new stdClass;
  if(!$search_fields) die("search_result: no fields");
  $result = array();
  
  $length = $options['length'] ?: 80; // how many characters before/after to show

  // todo: start/offset for pagination
  $limit = $options['limit'] ?: 20; // how many characters before/after to show
  
  $obj_fields = object_fields($obj_type);
  $key = get_object_key($obj_type);
  $title_field = get_object_descriptor($obj_type);
  
  if(!is_array($search_fields)) $search_fields = (array) $search_fields;
  if(count($search_fields) > 1) {
    $search_array = array();
    foreach($search_fields as $field) $search_array[$field] = "*$term*";
    $search[DB_LOGICAL_OR] = $search_array;
  } else {
    $field = $search_fields[0];
    $search[$field] = "*$term*";
  }
  
  if(in_array('language', $obj_fields)) $search['language'] = $_SESSION['lang'] ?: $siteObj->default_language;
  if(in_array('active', $obj_fields)) $search['active'] = 1;
  $search['site_id'] = $siteObj->id;
    
  $ids = find_objects($obj_type, $search, array('field' => $key, 'limit' => $limit));

  $debug = false;
  //if($obj_type == 'comment') $debug = true;
  
  if($debug) {
    echo("Search for $obj_type");
    dump($search);
    dump($ids);
  }
                     
  // $debug = true;
  $page_ids = array();
  foreach($ids as $id) {
    $resultObj = new stdClass;
    $obj_fields = $search_fields;
    if(in_array($obj_type, array('page_element', 'page_content'))) $obj_fields[] = 'page_id';
    if(in_array('path', $obj_fields)) $obj_fields[] = 'path';
    if($obj_type == 'comment') $obj_fields[] = 'article_id';
    
    $obj = get_object($obj_type, $id, $obj_fields);
    if($debug) dump($obj);
    foreach($search_fields as $search_field) {
      if($debug) echo("Looking for $term in $search_field of $obj_type $id<br>");
      $val = count($obj_fields) > 1 ? $obj->$search_field : $obj; // the value of the field containing term
      $val = strip_tags($val);
      $pos = stripos($val, $term); 
      if($pos !== FALSE) {
        if($page_id = $obj->page_id) $page_ids[$page_id] = 1;
        
        $start = max($pos - round($length/2), 0);
        $str = substr($val, $start, $length);
        if($debug) echo(" - Found $term in $search_field of $obj_type $id<br>");
        if($debug) echo(" Result: $str<br>");
              
        $title = $obj->$title_field;
        
        // find link
        if($obj->path) { // e.g. page_content
          $link = $obj->path;
        } else if($page_id = $obj->page_id) { // e.g. page_element
          $link = site_page_link($siteObj, get_object('site_page', $page_id));
        } else { // article, event, other
          switch($obj_type) {
            case 'article';
              $link = "/nieuws/?id=$id";
            break;
            case 'comment';
              $link = "/nieuws/?id=".$obj->article_id;
              $title = get_object('article', $obj->article_id, 'title');
            break;
            case 'event';
              $link = "/evenementen/?id=$id";
            break;
            default:
            break;
          }
        }
        
        //$link = "/foo/";
        $resultObj->title = $title;
        $resultObj->link = $link;        
        $resultObj->string = $str;
        $result[] = $resultObj;
        break;
      } else {
        if($debug) echo(" - NO: pos=$pos<br>");
      }
    }
    
  }
  
  // special handling; page_elements, repeated code, but what the heck
  if($obj_type == 'page_content') {
    $search = array();
    $search['site_id'] = $siteObj->id;
    $search['content'] = "*$term*";
    if(count($page_ids)) $search['page_id'] = array('!=', array_keys($page_ids)); // exclude those already found    
    $search['language'] = $_SESSION['lang'] ?: $siteObj->default_language;    
    $ids = find_objects('page_element', $search, array('field' => 'id', 'limit' => $limit));
    foreach($ids as $id) {
      $obj = get_object('page_element', $id, array('page_id', 'content'));
      $page_id = $obj->page_id;
      if($page_ids[$page_id]) continue;
      $page_ids[$page_id] = 1;
      $pageObj = get_object('site_page', $page_id);

      $val = strip_tags($obj->content);
      $pos = stripos($val, $term); 
      $start = max($pos - round($length/2), 0);
      $str = substr($val, $start, $length);

      $resultObj = new stdClass;
      $resultObj->title = $pageObj->name; // todo: use page content title
      $resultObj->link = site_page_link($siteObj, $pageObj);
      $resultObj->string = $str;
      $result[] = $resultObj;
      
      //echo("Found $term in page_el $id on page $page_id<br>");     
    }
  }
  
  
  if($debug) dump($result);
  
  return $result;
}


function traveler_dependencies($siteObj, $pageObj, $options = array()) {
  global $__header, $u_id, $u_level;
  $auth_edit = $options['auth_edit'] || $u_level >= USER_LEVEL_STAFF;
  
  $gallery_page = false;
  $page_type = $pageObj->page_type;
  if($page_type == 1401) { // view art
    $gallery_page = true;
  } elseif($page_type == 1120) { // edit gallery
    $gallery_page = true;
  }
  if($gallery_page) {
    $__header['css'][] = "/afr/css/sass-screen.css"; /** todo: remove - get rid of sprites */ 
    $__header['css'][] = "/afr/css/afr_gallery.css";  
  }

  $template = '';
  switch($siteObj->template_id) {
  case 1019:
    $template = 'traveler';
    break;
  case 1018:
    $template = 'epona';
    break;
  default:
    break;
  }
  
  $ver = $_SESSION['version'] ?: date('md');
  $lang = strtolower($_SESSION['language']);
  
  $__header['css'][] = "/afr/css/afr_base.css?v=$ver";  
  $__header['css'][] = "/afr/css/afr_rental.css?v=$ver";  
  $__header['css'][] = "/afr/css/afr_tooltip.css";
  if($u_id) $__header['css'][] = "/afr/css/afr_cms.css?ver=$ver";
  if(is_file($_SERVER['DOCUMENT_ROOT']."/css/site_".$siteObj->shortname.".css")) $__header['css'][] = "/css/site_".$siteObj->shortname.".css";
  $__header['css'][] = "//fonts.googleapis.com/css?family=Roboto:400,300,100,500,700";
  $__header['css'][] = "//fonts.googleapis.com/css?family=Open+Sans:400italic,400,300,600";
  //$__header['css'][] = "/afr/bower/bootstrap/dist/css/bootstrap.min.css";
  $__header['css'][] = "//maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css";
  
  

  //$__header['css'][] = "/afr/bower/font-awesome/css/font-awesome.min.css";
  $__header['css'][] = "/afr/font/afr/styles.css";

  if($template == 'traveler') {  
    $__header['css'][] = "/traveler/css/icomoon.css";
    $__header['css'][] = "/traveler/css/styles.css?v=$ver";
    $__header['css'][] = "/traveler/css/mystyles.css?v=$ver";
  }
  
  $dtp = 1;
  $tp = 1; /** which timepicker */
   
  if($template != 'epona') $__header['css'][] = "/css/site.css?ver=$ver&t=1";

  //$__header['css'][] = "//netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap-glyphicons.css";
  $__header['css'][] = "/afr/bower/fancybox/source/jquery.fancybox.css";
  $__header['css'][] = "/afr/bower/summernote/dist/summernote.css";
   
  $__header['css'][] = "/afr/bower/bootstrap3-wysihtml5-bower/dist/bootstrap3-wysihtml5.min.css";
   
   
  $__header['css'][] = "/afr/bower/bootstrap-toggle/css/bootstrap-toggle.min.css";
  $__header['css'][] = "/afr/bower/bootstrap-modal/css/bootstrap-modal-bs3patch.css";
  $__header['css'][] = "/afr/bower/bootstrap-modal/css/bootstrap-modal.css";
  
  $__header['css'][] = "https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.4/css/bootstrap-datepicker3.min.css";
  
  
  //$__header['css'][] = "/afr/bower/jquery-timepicker/jquery.ui.timepicker.css";

  if($dtp == 1) {
    //$__header['css'][] = "/afr/jquery/periodpicker/build/jquery.periodpicker.min.css";
  } else {
    $__header['css'][] = "/afr/bower/smalot-bootstrap-datetimepicker/css/bootstrap-datetimepicker.min.css";
  }
  
  if($tp == 1) {
    $__header['css'][] = "/afr/bower/jquery-timepicker-jt/jquery.timepicker.css";
  } else {
    $__header['css'][] = "/afr/bower/bootstrap-timepicker/css/bootstrap-timepicker.css";
  }

  $__header['css'][] = "/afr/bower/ionrangeslider/css/ion.rangeSlider.css";
  $__header['css'][] = "/afr/bower/bootstrap-star-rating/css/star-rating.css";
  $__header['css'][] = "/afr/css/google_pac.css"; 
  $__header['css'][] = "/afr/bower/select2/select2.css";    
  $__header['css'][] = "/afr/bower/flag-icon-css/css/flag-icon.min.css";    
  $__header['css'][] = "/afr/bower/bootstrap-social/bootstrap-social.css";    
  $__header['css'][] = "/afr/bower/intl-tel-input/build/css/intlTelInput.css"; /* Note: must set .iti-flag {background-image: url("/bower/intl-tel-input/build/img/flags.png");} in css */    
  $__header['css'][] = "/afr/bower/magnific-popup/dist/magnific-popup.css";
  
  $__header['css'][] = "/afr/bower/addtocalendar/atc.css?foo=bar";
    
  // top scripts
  $__header['base_scripts'][] = "/afr/bower/jquery/dist/jquery.min.js"; // these are loaded first
  $__header['base_scripts'][] = "/afr/bower/jquery-ui/ui/minified/jquery-ui.min.js";

  // moment + moment-range, using node
  $__header['base_scripts'][] = "/afr/node/moment/moment.js";    
  $__header['base_scripts'][] = "/afr/node/moment-range/dist/moment-range.js";
  $__header['base_scripts'][] ="script:window['moment-range'].extendMoment(moment)";
  
  if($lang !== 'en') $__header['base_scripts'][] = "/afr/bower/moment/locale/{$lang}.js";
  
  //$__header['base_scripts'][] = "/afr/bower/bootstrap-datepicker/js/bootstrap-datepicker.js";
  $__header['base_scripts'][] = "https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.4/js/bootstrap-datepicker.min.js";
  
  $__header['base_scripts'][] = "https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.4/js/bootstrap-datepicker.min.js";
  
  
  //$__header['base_scripts'][] = 'script:$.widget.bridge("uibutton", $.ui.button);$.widget.bridge("uitooltip", $.ui.tooltip);'; // avoid tooltip confict jquery/bootstrap
  //$__header['base_scripts'][] = "/traveler/js/bootstrap.js";
  //$__header['base_scripts'][] = "/afr/bower/bootstrap/dist/js/bootstrap.min.js";
  $__header['base_scripts'][] = "//maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js";
  $__header['base_scripts'][] = "https://use.fontawesome.com/a22cbf3bb2.js";
  $__header['base_scripts'][] = "/afr/js/afr.js?v=$ver";
  if($u_id) $__header['base_scripts'][] = "/afr/js/afr_cms.js?v=$ver";

  //if($siteObj->property_site) $__header['base_scripts'][] = "/afr/js/afr_property.js?v=$ver";
  if($siteObj->property_site || $siteObj->property_type) $__header['base_scripts'][] = "/afr/js/afr_rental.js?v=$ver";

  $__header['base_scripts'][] = GMAP_API;
  $__header['base_scripts'][] = "https://cdn.rawgit.com/googlemaps/v3-utility-library/master/markerwithlabel/src/markerwithlabel.js";
  
  $__header['base_scripts'][] = "/afr/js/google_pac.js?v=$ver";
  
  $__header['base_scripts'][] = "/afr/bower/fancybox/source/jquery.fancybox.pack.js";
  $__header['base_scripts'][] = "/afr/bower/summernote/dist/summernote.min.js";
  $__header['base_scripts'][] = "/afr/bower/bootstrap3-wysihtml5-bower/dist/bootstrap3-wysihtml5.all.min.js";  
  

  // end scripts
  $__header['end_scripts'][] = "/js/main.js?v=$ver";

  if($template == 'traveler') {
    $__header['end_scripts'][] = "/traveler/js/slimmenu.js";
    $__header['end_scripts'][] = "/traveler/js/nicescroll.js";
    $__header['end_scripts'][] = "/traveler/js/dropit.js";
    //$__header['end_scripts'][] = "/traveler/js/ionrangeslider.js";
    $__header['end_scripts'][] = "/traveler/js/icheck.js";
    $__header['end_scripts'][] = "/traveler/js/fotorama.js";
    $__header['end_scripts'][] = "/traveler/js/typeahead.js";
    $__header['end_scripts'][] = "/traveler/js/card-payment.js";
    $__header['end_scripts'][] = "/traveler/js/owl-carousel.js";
    $__header['end_scripts'][] = "/traveler/js/fitvids.js";
    $__header['end_scripts'][] = "/traveler/js/tweet.js";
    $__header['end_scripts'][] = "/traveler/js/gridrotator.js";
  }
  
  $__header['end_scripts'][] = "/afr/bower/magnific-popup/dist/jquery.magnific-popup.min.js";
  
  //$__header['end_scripts'][] = "/afr/lib/selectToAutocomplete/jquery.select-to-autocomplete.js";
  

  $__header['end_scripts'][] = "/afr/bower/select-to-autocomplete/jquery.select-to-autocomplete.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-validator/dist/validator.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-confirmation2/bootstrap-confirmation.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-toggle/js/bootstrap-toggle.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-modal/js/bootstrap-modalmanager.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-modal/js/bootstrap-modal.js";
  //$__header['end_scripts'][] = "/afr/lib/selectToAutocomplete/jquery.select-to-autocomplete.js";
  //$__header['end_scripts'][] = "/afr/bower/jquery-timepicker/jquery.ui.timepicker.js";
  
  if($tp == 1) {
    //$__header['end_scripts'][] = "/afr/jquery/periodpicker/build/jquery.periodpicker.full.min.js";
  } else {
    $__header['end_scripts'][] = "/afr/bower/bootstrap-timepicker/js/bootstrap-timepicker.js";
  }
  
  if($dtp == 1) {
    //$__header['end_scripts'][] = "/afr/bower/datetimepicker/build/jquery.datetimepicker.min.js";
  } else {
    $__header['end_scripts'][] = "/afr/bower/smalot-bootstrap-datetimepicker/js/bootstrap-datetimepicker.min.js";
  }
  
  $__header['end_scripts'][] = "/afr/bower/ionrangeslider/js/ion.rangeSlider.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-star-rating/js/star-rating.min.js";
  $__header['end_scripts'][] = "/afr/bower/select2/select2.min.js";    
  $__header['end_scripts'][] = "/afr/bower/jquery.countdown/dist/jquery.countdown.js";    
  $__header['end_scripts'][] = "/afr/bower/intl-tel-input/build/js/intlTelInput.min.js";    
  $__header['end_scripts'][] = "/afr/bower/jquery.parallax/jquery.parallax.js"; 
  $__header['end_scripts'][] = "/afr/bower/accounting.js/accounting.min.js"; 
  $__header['end_scripts'][] = "/afr/bower/character-countdown/build/characterCountdown.min.js"; 
  $__header['end_scripts'][] = "/afr/bower/addtocalendar/atc.min.js"; 
  $__header['end_scripts'][] = "/afr/bower/handlebars/handlebars.min.js";
  $__header['end_scripts'][] = "/afr/bower/jquery-truncate-html/jquery.truncate.js";

  
  
  //$__header['end_scripts'][] = "/traveler/js/countdown.js";
  if($page_type == 1120) $__header['end_scripts'][] = "/afr/bower/zeroclipboard/dist/ZeroClipboard.min.js";
  
  if($template == 'traveler') $__header['end_scripts'][] = "/traveler/js/custom.js?v=$ver";    

  if($auth_edit) {
    $__header['css'][] = "/afr/bower/CodeMirror/lib/codemirror.css"; 
    $__header['end_scripts'][] = "/afr/bower/CodeMirror/lib/codemirror.js"; 
    $__header['end_scripts'][] = "/afr/bower/CodeMirror/mode/smarty/smarty.js"; 
    //$__header['end_scripts'][] = "/afr/bower/CodeMirror/mode/htmlmixed/htmlmixed.js"; 
  }
  if($siteObj->google_tag_id) $__header['end_scripts'][] = "/afr/js/lunametrics.js?v=$ver"; 

  //dump($__header);
}


/** new - for all templates */
function site_dependencies($siteObj, $pageObj, $options = array()) {
  global $__header, $u_id, $u_level;
  $scripts = $styles = $header_styles = $header_scripts = [];
  
  $auth_edit = $options['auth_edit'] || $u_level >= USER_LEVEL_STAFF;
  
  $gallery_page = false;
  $page_type = $pageObj->page_type;
  if($page_type == 1401) { // view art
    $gallery_page = true;
  } elseif($page_type == 1120) { // edit gallery
    $gallery_page = true;
  }
  if($gallery_page) {
    $styles[] = "/afr/css/sass-screen.css"; /** todo: remove - get rid of sprites */ 
    $styles[] = "/afr/css/afr_gallery.css";  
  }

  $template = '';
  switch($siteObj->template_id) {
  case 1019:
    $template = 'traveler';
    break;
  case 1016:
    $template = 'epona';
    break;
  default:
    break;
  }
  
  $ver = $_SESSION['version'] ?: date('md');

  /** above the fold */
  $header_styles[] = "/afr/bower/bootstrap/dist/css/bootstrap.min.css";
  $header_styles[] = "/afr/css/afr_base.css?v=$ver";  
  if($template == 'traveler') $header_styles[] = "/traveler/css/styles.css?v=$ver";
  $header_styles[] = "/css/site.css?ver=$ver";

  /** below the fold */
  $styles[] = "/afr/css/afr_rental.css?v=$ver";  
  $styles[] = "/afr/css/afr_tooltip.css";
  if($u_id) $styles[] = "/afr/css/afr_cms.css?ver=$ver";
  if(is_file($_SERVER['DOCUMENT_ROOT']."/css/site_".$siteObj->shortname.".css")) $styles[] = "/css/site_".$siteObj->shortname.".css";
  $styles[] = "//fonts.googleapis.com/css?family=Roboto:400,300,100,500,700";
  $styles[] = "//fonts.googleapis.com/css?family=Open+Sans:400italic,400,300,600";

  $styles[] = "/afr/bower/font-awesome/css/font-awesome.min.css";
  $styles[] = "/afr/font/afr/styles.css?ver=$ver";

  if($template == 'traveler') {  
    $styles[] = "/traveler/css/icomoon.css";
  }
  
  $tp = 1; /** which timepicker */
   
  $styles[] = "//netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap-glyphicons.css";
  $styles[] = "/afr/bower/fancybox/source/jquery.fancybox.css";
  $styles[] = "/afr/bower/summernote/dist/summernote.css";
   
  $styles[] = "/afr/bower/bootstrap3-wysihtml5-bower/dist/bootstrap3-wysihtml5.min.css";
   
   
  $styles[] = "/afr/bower/bootstrap-toggle/css/bootstrap-toggle.min.css";
  $styles[] = "/afr/bower/bootstrap-modal/css/bootstrap-modal-bs3patch.css";
  $styles[] = "/afr/bower/bootstrap-modal/css/bootstrap-modal.css";

  $styles[] = "/afr/bower/smalot-bootstrap-datetimepicker/css/bootstrap-datetimepicker.min.css";
  
  $styles[] = "https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.4/css/bootstrap-datepicker3.min.css";
  
  
  //$styles[] = "/afr/bower/jquery-timepicker/jquery.ui.timepicker.css";
  if($tp == 1) {
    $styles[] = "/afr/bower/jquery-timepicker-jt/jquery.timepicker.css";
  } else {
    $styles[] = "/afr/bower/bootstrap-timepicker/css/bootstrap-timepicker.css";
  }

  $styles[] = "/afr/bower/ionrangeslider/css/ion.rangeSlider.css";
  $styles[] = "/afr/bower/bootstrap-star-rating/css/star-rating.css";
  $styles[] = "/afr/css/google_pac.css"; 
  $styles[] = "/afr/bower/select2/select2.css";    
  $styles[] = "/afr/bower/flag-icon-css/css/flag-icon.min.css";    
  $styles[] = "/afr/bower/bootstrap-social/bootstrap-social.css";    
  $styles[] = "/afr/bower/intl-tel-input/build/css/intlTelInput.css"; /* Note: must set .iti-flag {background-image: url("/bower/intl-tel-input/build/img/flags.png");} in css */    
  $styles[] = "/afr/bower/magnific-popup/dist/magnific-popup.css";
  
  $styles[] = "/afr/bower/addtocalendar/atc.css?foo=bar";
    
  /** above the fold */
  $header_scripts[] = "https://ajax.googleapis.com/ajax/libs/jquery/2.2.4/jquery.min.js";

  /** below the fold */
  $scripts[] = "/afr/bower/jquery-ui/ui/minified/jquery-ui.min.js";
  $scripts[] = "/afr/bower/moment/moment.js";    
  $scripts[] = "/afr/bower/moment-range/lib/moment-range.js";
  
  //$scripts[] = "/afr/bower/bootstrap-datepicker/js/bootstrap-datepicker.js";
  $scripts[] = "https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.4/js/bootstrap-datepicker.min.js";
  

  // $scripts[] = 'script:$.widget.bridge("uibutton", $.ui.button);$.widget.bridge("uitooltip", $.ui.tooltip);'; // avoid tooltip confict jquery/bootstrap
  //$scripts[] = "/traveler/js/bootstrap.js";
  $scripts[] = "/afr/bower/bootstrap/dist/js/bootstrap.min.js";  
  $scripts[] = "/afr/js/afr.js?v=$ver";
  if($u_id) $scripts[] = "/afr/js/afr_cms.js?v=$ver";
  //if($siteObj->property_site) $scripts[] = "/afr/js/afr_property.js?v=$ver";
  if($siteObj->property_site || $siteObj->property_type) $scripts[] = "/afr/js/afr_rental.js?v=$ver";

  $scripts[] = GMAP_API;
  $scripts[] = "https://cdn.rawgit.com/googlemaps/v3-utility-library/master/markerwithlabel/src/markerwithlabel.js";

  $scripts[] = "/afr/js/google_pac.js?v=$ver";
  $scripts[] = "/afr/bower/fancybox/source/jquery.fancybox.pack.js";
  $scripts[] = "/afr/bower/summernote/dist/summernote.min.js";
  $scripts[] = "/afr/bower/bootstrap3-wysihtml5-bower/dist/bootstrap3-wysihtml5.all.min.js";
  

  // end scripts
  $scripts[] = "/js/main.js?v=$ver";

  if($template == 'traveler') {
    $scripts[] = "/traveler/js/slimmenu.js";
    $scripts[] = "/traveler/js/nicescroll.js";
    $scripts[] = "/traveler/js/dropit.js";
    //$scripts[] = "/traveler/js/ionrangeslider.js";
    $scripts[] = "/traveler/js/icheck.js";
    $scripts[] = "/traveler/js/fotorama.js";
    $scripts[] = "/traveler/js/typeahead.js";
    $scripts[] = "/traveler/js/card-payment.js";
    $scripts[] = "/traveler/js/owl-carousel.js";
    $scripts[] = "/traveler/js/fitvids.js";
    $scripts[] = "/traveler/js/tweet.js";
    $scripts[] = "/traveler/js/gridrotator.js";
  }
  
  $scripts[] = "/afr/bower/magnific-popup/dist/jquery.magnific-popup.min.js";
  
  //$scripts[] = "/afr/lib/selectToAutocomplete/jquery.select-to-autocomplete.js";      
  $scripts[] = "/afr/bower/bootstrap-validator/dist/validator.min.js";
  $scripts[] = "/afr/bower/bootstrap-confirmation2/bootstrap-confirmation.js";
  $scripts[] = "/afr/bower/bootstrap-toggle/js/bootstrap-toggle.min.js";
  $scripts[] = "/afr/bower/bootstrap-modal/js/bootstrap-modalmanager.js";
  $scripts[] = "/afr/bower/bootstrap-modal/js/bootstrap-modal.js";
  //$scripts[] = "/afr/lib/selectToAutocomplete/jquery.select-to-autocomplete.js";
  //$scripts[] = "/afr/bower/jquery-timepicker/jquery.ui.timepicker.js";
  
  if($tp == 1) {
    $scripts[] = "/afr/bower/jquery-timepicker-jt/jquery.timepicker.js";
  } else {
    $scripts[] = "/afr/bower/bootstrap-timepicker/js/bootstrap-timepicker.js";
  }
  
  
  $scripts[] = "/afr/bower/smalot-bootstrap-datetimepicker/js/bootstrap-datetimepicker.min.js";
  
  $scripts[] = "/afr/bower/ionrangeslider/js/ion.rangeSlider.min.js";
  $scripts[] = "/afr/bower/bootstrap-star-rating/js/star-rating.min.js";
  $scripts[] = "/afr/bower/handlebars/handlebars.min.js";
  
  $scripts[] = "/afr/bower/select2/select2.min.js";    
  $scripts[] = "/afr/bower/jquery.countdown/dist/jquery.countdown.js";    
  $scripts[] = "/afr/bower/intl-tel-input/build/js/intlTelInput.min.js";    
  $scripts[] = "/afr/bower/jquery.parallax/jquery.parallax.js"; 
  $scripts[] = "/afr/bower/accounting.js/accounting.min.js"; 
  $scripts[] = "/afr/bower/character-countdown/build/characterCountdown.min.js"; 
  $scripts[] = "/afr/bower/addtocalendar/atc.min.js"; 

  
  //$scripts[] = "/traveler/js/countdown.js";
  if($page_type == 1120) $scripts[] = "/afr/bower/zeroclipboard/dist/ZeroClipboard.min.js";
  
  if($template == 'traveler') $scripts[] = "/traveler/js/custom.js?v=$ver";    

  if($auth_edit) {
    $styles[] = "/afr/bower/CodeMirror/lib/codemirror.css"; 
    $scripts[] = "/afr/bower/CodeMirror/lib/codemirror.js"; 
    $scripts[] = "/afr/bower/CodeMirror/mode/smarty/smarty.js"; 
    //$scripts[] = "/afr/bower/CodeMirror/mode/htmlmixed/htmlmixed.js"; 
  }
  if($siteObj->google_tag_id) $scripts[] = "/afr/js/lunametrics.js?v=$ver"; 

  //dump($__header);
  if(!$pageObj->html || !is_object($pageObj->html)) $pageObj->html = new stdClass;
  
  $pageObj->html->header_scripts = $header_scripts;
  $pageObj->html->header_styles = $header_styles;
  $pageObj->html->scripts = $scripts;
  $pageObj->html->styles = $styles;
  return $pageObj;
}

/** The global site template (<HTML><Header><body>)
    Replaces old site_html_document and alls its dependencies */
    
function site_application($siteObj, $pageObj, $options = array()) {

  $scope = new stdClass;
  $nav_class = 'navbar-fixed-top';
  $templateData = array("nav_class" => $nav_class, "login" => $login, "provider_keys" => $provider_keys);
  $content_options['base_styles'] = false; 

  // Begin Controller, data is saved in scope, accessible in templates  
  $pageObj = apply_controller($siteObj, $pageObj, $controllerData);
  $scope = $_SESSION['scope'] = $pageObj->scope;
    
  // load page content (template, template_id might be overriden by controller)  
  if($scope->redirect) redirect($scope->redirect);  
  if(!$content_loaded) $page_content = site_content($siteObj, $pageObj, $content_options);
    
  $edit_forms = site_edit_forms($siteObj, $pageObj, []);
  //$pageElements->content = $edit_forms.$page_content;  
  //$pageObj->html->elements = $pageElements;
  
  $tpl_filename = "_html-index.html";  
  $pageObj = site_dependencies($siteObj, $pageObj, []); // load dependencies (scripts, css) 

  //dump($pageObj);
  return $pageObj;

 
  // Begin Controller, data is saved in scope, accessible in templates
  /** old
  $pageObj = apply_controller($siteObj, $pageObj, $options);  
  $scope = $_SESSION['scope'] = $pageObj->scope;
  if($scope->redirect) redirect($scope->redirect);
    
  $options['parse'] = false;
  $pageObj->template = site_page_template($siteObj, $pageObj, $options);
  //echo("page template = $page_template<br>");

  $template = pick_first($options['template'], $pageObj->site_template, $siteObj->template, "default");
  $filename = "template/$template/index.html";
  $tpl_filename = smarty_preparse_template($filename); // parse our own template structure, write smarty template
  if(!$tpl_filename) die("site_output: preparse $filename returned null - template=$template");
  */
  
}

function site_render($siteObj, $pageObj, $options = array()) {
  //$body = $pageObj->html->body;
  //dump($body);
  
  $template = pick_first($options['template'], $pageObj->site_template, $siteObj->template, "default");  
  $filename = "template/$template/index.html";

  $filename = "html/traveler.html";  
  $tpl_filename = smarty_preparse_template($filename); // parse our own template structure, write smarty template
  if(!$tpl_filename) die("site_output: preparse $filename returned null - template=$template");

  $output = smarty_parse_template($siteObj, $pageObj, $tpl_filename, $options); // now run in through smarty for further parsing    
  return $output;
}