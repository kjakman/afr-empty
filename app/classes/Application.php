<?php
namespace AFR;

use Monolog\Logger;
use Monolog\Handler\StreamHandler;
use Symfony\Router;
//use Monolog\Handler\StreamHandler;

class Application {
    
    public $config;     
    
    public $site;
    public $site_id;
    public $page;
    public $page_id;
    public $content_id;                                     
    public $language;

    /** following based on path and page */
    public $controller;
    public $action;
    public $name;
    public $obj_id;
    public $obj_type;
    public $view;
    public $subview;
    public $template;
    public $subtemplate;
    
    public $path;
    public $model;
    
    //store the URL values on object creation
    public function __construct($siteObj, $userObj)
    {
      
        $this->model = new Model();
        $this->site = $siteObj;
        $this->site_id = $siteObj->id;
        $this->user = $userObj ?: null;
        $this->user_id = $userObj ? $userObj->id : 0;
        $this->user_level = $userObj ? $userObj->user_level : 0;
        $this->uri = $uri = $_SERVER['REQUEST_URI'];
        
        $parts = parse_url($uri);
        $this->path = rtrim($parts['path'],'/'); // remove trailing slash in case nginx didn't;
        $this->query = $parts['query'];

        /** todo: move below to config */
        $site_url = $_SERVER['HTTP_HOST']; // e.g. www.afr.com
        
        
        $host_domains = explode(".", $site_url);
        $host_tld = array_pop($host_domains); // e.g. com
        $host_port = 80;
        if(strpos($host_tld, ':')) list($host_tld, $host_port) = explode(":", $host_tld);
        $host_dom = array_pop($host_domains); // e.g apartments-for-rent
        $host_sub =  count($host_domains) ? array_pop($host_domains) : ''; // e.g. www
        
        $config = new \stdClass;
        $shortname = $siteObj->shortname;
        
        $config->live = $live = $host_sub == "" || $host_sub == 'www' ? 1 : 0;
        $config->deployment = $deployment = $live ? 'live' : $host_sub;
        
        $config->app_root = $live ? "/web/comps/php/afr" : "/web/comps/php/afr-dev";
        $config->doc_root = rtrim($_SERVER['DOCUMENT_ROOT'], '/');        
        $config->data_dir = $data_dir = $live ? "/web/data/{$shortname}" : "/web/data-dev/{$shortname}";                
        $config->log_dir = $log_dir = "{$data_dir}/log";                
        $this->config = $config;

        // $container = DI\ContainerBuilder::buildDevContainer();

        // create a log channel
        $this->logger = $logger = new \Monolog\Logger("afr");
        $logger->pushHandler(new StreamHandler("{$log_dir}/afr-{$deployment}.txt", Logger::INFO));        
        //$logger->pushHandler(new StreamHandler("{$log_dir}/afr-{$deployment}.txt", Logger::DEBUG));        

        $logger->info('Created app', (array) $config);
        
    }
    
    public function run()
    {
        global $__PAGE; /** remmove later - needed for now by functional part */

        // add records to the log

        //$w = '-a-zA-Z0-9@:%._\+~#='; // characters allowed in url (no tilde or period)
        $w = 'a-zA-Z0-9-';
        /** look for page matching route */

        /** [lang?][controller?][action?] */
        Router::route("(/[a-z]{2})?", function ($lang, $controller, $action) {
            return ['rule' => 1, 'lang' => ltrim($lang,'/'), 'controller' => 'home', 'action' => '', 'name' => '', 'obj_id' => '', 'subview' => ''];
        });         
        
        /** [lang?][controller?][action?] */
        Router::route("(/[a-z]{2})?(/[$w]{3,})?(/[$w]{3,})?", function ($lang, $controller, $action) {
            return ['rule' => 2, 'lang' => ltrim($lang,'/'), 'controller' => ltrim($controller,'/'), 'action' => ltrim($action,'/'), 'name' => '', 'obj_id' => '', 'subview' => ''];
        });         

        /** [lang?][controller?][id?][view?] */
        /** allows us skip the action for view so /product/33 instead of /product/view/33 */
        Router::route("(/[a-z]{2})?/([$w]{3,})/([$w]+~)?(\d+)(/[\w-_]+)?", function ($lang, $controller, $name, $obj_id, $subview) {
            return ['rule' => 3, 'lang' => ltrim($lang,'/'), 'controller' => $controller, 'action' => 'view', 'name' => rtrim($name,'~'), 'obj_id' => $obj_id, 'subview' => ltrim($subview,'/')];
        });

        /** [lang?][controller?][action][id?][view?] */
        Router::route("(/[a-z]{2})?/([$w]{3,})/([$w]{3,})/([\w-_]+~)?(\d+)(/[\w]+)?", function ($lang, $controller, $action, $name, $obj_id,$subview) {
            return ['rule' => 4, 'lang' => ltrim($lang,'/'), 'controller' => $controller, 'action' => $action, 'name' => rtrim($name,'~'), 'obj_id' => $obj_id, 'subview' => ltrim($subview,'/')];
        });

        $data = Router::execute($this->path) ?: [];
        if(!$data['action']) $data['action'] = 'index'; 
        foreach($data as $k => $v) $this->$k = $v;    
        
         
        $this->template = $tpl = "{$data['controller']}/{$data['action']}";
                                             
        $this->logger->info("App::run: uri:($this->uri) tpl: {$tpl} Path: {$this->path} Request: ".$_SERVER['REQUEST_URI'], $data);
                                                                    
        /** expensive DB look-up, move to below ? */
        if($page = $this->route()) {
            if($page->user_level && $page->user_level > $this->user_level) {
                redirect_login($this->path);
            }
                                                    
            if($page->controller) $this->controller = $controller = $page->controller;            
            if($page->template)   $this->template = $page->template;
            if($page->language) {
                $this->setLanguage($page->language);
            }
            $this->page = $__PAGE = $page;
            $this->logger->info("Found page: tpl={$page->template}");
                                
        } else {
            $this->logger->info("No page: tpl={$page->template}");
        }
                
        
        /** get scope - try new controller class */
        if($ctrl = $this->createController()) {            
            $scope = $this->scope = $ctrl->executeAction();  /** execute controller action  */
        } elseif(function_exists("controller_{$this->controller}")) { /** fallback on scope from old controller function */
            $scope = $this->scope = call_user_func("controller_{$this->controller}", $this->site, $this->page);
        } else {
            $ctrl = new Error("badUrl: controller {$this->controller} not found", 404);
            $scope = $this->scope = $ctrl->executeAction();            
        }
             
        if($scope->subtemplate) $this->subtemplate = $scope->subtemplate; /** for partial views */        
        
        /** render template with scope */
        global $__header;
        $this->header = $__header;
        $partial = isset($_GET['_pv']) ? true : false;
        $this->logger->info("App::run calling render on t={$this->template} st={$this->subtemplate} tpl={$partial}");
        
        
        $output = $this->render($partial);
        echo($output);
    }

    public function setLanguage($language)
    {
        $this->language = $language;
    }

    
    protected function render($partial = false)
    {
        $viewloc = 'views/' . get_class($this) . '/' . $this->action . '.php';
        
        $template = ($partial && $this->subtemplate) ? $this->subtemplate : $this->template;
        
        $this->logger->info("Render: tpl={$template} partial:{$partial}", $_GET);
        
        $view = new \AFR\View($this, $template);        
        $scope = $this->scope;
        
        $output = $view->render();
        return $output;
        
    }
    
    
    /** return "page" (template, controller, user-level) based on data from path */
    protected function route($data)
    {
        /** first, try config file - yaml */
        
        /** then try database */
        $model = $this->model;
        $path = "/{$this->controller}/"; // look in database for page for this path
        if($this->action && $this->action != 'index') $path = "{$path}{$this->action}/";
        
        $search = ['site_id' => $this->site_id, 'path' => $path];
        $this->logger->debug("App::route: Looking for {$path} ctrl: {$this->controller} action: {$this->action}");
        $content = $model->find('page_content', $search);
        if(!$content) return null;
        
        $this->content_id = $content->id;
        $this->page_id = $content->page_id;
        $page = Model::get('site_page', $this->page_id);
        if(!$page) die("No page with id={$this->page_id}"); /** todo: exception */
        
        $page = object_merge($content, $page);
        $page->content_id = $content->id;
        return $page;
    }

    /** establish the requested controller as an object
      * performs routing based on query vars 
      */
    protected function createController() {
        $controller = $this->controller;
        
        include_once("controllers/".ucfirst($controller).".php");

        $namespace = "AFR\\Controller\\";
        if(class_exists($namespace.ucfirst($this->controller))) { // new; allow define controller w/o page in db
            $this->controllerClass = ucfirst($this->controller);
            
            $parents = class_parents('\\AFR\\Controller\\'.$this->controllerClass);

            //does the class extend the controller class?
            if (in_array($namespace."BaseController",$parents)) {
                
                //does the class contain the requested method?
                if (method_exists($namespace.$this->controllerClass,$this->action)) {
                    $ctrl = $namespace.$this->controllerClass;
                    
                    /** check if method matches obj_id and subview parameters */
                    $reflection = new \ReflectionMethod($ctrl, $this->action);
                    $num_params = $reflection->getNumberOfParameters();
                    $rparams = $reflection->getParameters();                    
                    $params = []; /** assoc. array of param_name => required */
                    foreach ($rparams as $param) $params[$param->getName()] = $param->isOptional() ? 0 : 1;
                    if($this->subview && !isset($params['subview'])) return new Error("badUrl: no subview allowed for {$ctrl}::{$this->action}", 404);
                    if($this->obj_id && !isset($params['obj_id'])) return new Error("badUrl: no object id allowed for {$ctrl}::{$this->action}", 404); 
                    if(isset($params['obj_id']) && $params['obj_id'] && !$this->obj_id) return new Error("badUrl: object id required for {$ctrl}::{$this->action}", 404); 
                    if(isset($params['subview']) && $params['subview'] && !$this->subview) return new Error("badUrl: subview required for {$ctrl}::{$this->action}", 404); 

                    return new $ctrl($this, $this->template, $this->action, $this->obj_id, $this->subview);
                    
                } else {
                    //bad method error
                    return new Error("badUrl: no method {$this->action} for {$this->controller}", 404);
                }
            } else {
                //bad controller error
                return new Error("badUrl: not a child of BaseController", 404);
            }
        } else {
            return null;
            //die("No content or class for path={$path}");
        }
    }
}



/** Helper classes */

class Error {
    private $error;
    private $data;
    private $status;
    public function __construct($error, $status=404, $vars='') {
        $this->data = $vars;
        $this->status = $status;
        $this->error = $error;
    }
    public function executeAction() {
        
        $error = $this->error ?: "unknown error";
        echo("Error: {$error}<br>");
        if($path = $this->path) echo("Path: {$path}");
    }
}