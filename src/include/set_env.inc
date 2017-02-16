<?php

$expires = 3600*24*30; // 30 days (in seconds)
set_time_limit(90); // increase max allowed execution time.

header('Content-Type:text/html; charset=UTF-8');
header('Expires: '.gmdate('D, d M Y H:i:s', time()+$expires).' GMT', false);
ini_set("session.cache_expire", 30 * 24 * 60); // 30 days
ini_set("session.gc_maxlifetime","10800"); // default is 1440, which is only 24 minutes
ini_set("session.bug_compat_warn","off");
ini_set("display_errors", 1);
define("UPPERCASE", 0);
define("LOWERCASE",1);
define("TITLECASE", 2);
define("CAPITALIZE", 3);
define("CAPS", 3);

error_reporting( error_reporting() & ~E_NOTICE & ~E_WARNING);

// domain 
$site_url = $_SERVER['HTTP_HOST']; // e.g. www.afr.com
$host_domains = explode(".", $site_url);
$host_tld = array_pop($host_domains); // e.g. com
$host_port = 80;
if(strpos($host_tld, ':')) list($host_tld, $host_port) = explode(":", $host_tld);
$host_dom = array_pop($host_domains); // e.g apartments-for-rent
$host_sub =  count($host_domains) ? array_pop($host_domains) : ''; // e.g. www
$host_domain = $site_domain = "$host_dom.$host_tld"; // e.g afr.com
$host_protocol = $_SERVER['HTTPS'] == 'on' ? "https" : "http";

$referer = $_SERVER['HTTP_REFERER'];

$system_cache_dir = $_SESSION['system_cache_dir'] = "/web/cache/";
$system_log_file = $_SESSION['system_log_file'] = $_SESSION['main_log'] = $main_log = 'system_log.txt';

$app_dir = $live ? 'afr' : 'afr-dev';
if($staging) $app_dir = 'apt-staging';
$doc_root = rtrim($_SERVER['DOCUMENT_ROOT'], '/').'/';
$app_root = "/web/comps/php/{$app_dir}";
set_include_path(get_include_path().PATH_SEPARATOR."{$app_root}/include".PATH_SEPARATOR."{$app_root}/includes".PATH_SEPARATOR."{$doc_root}/afr");

session_start();       
if(strpos($_SERVER['REQUEST_URI'], 'act=logout')) {
  echo("logging out..");
  session_unset(); // Destroy session on log out
}
/** get rid of all session vars except those really needed (user/site/lang/deployment) */
$_SESSION['auth_token'] = $_SESSION['auth_token'] ?: md5(rand(0, 100000)); // random token
$_SESSION['version'] = $version=1484925886; // used for cachebusting. Don't change, hotfix.sh depends on this exact line.
$_SESSION['start_time'] = microtime(true); // start timer
$_SESSION['scope'] = NULL;
$_SESSION['debug_db'] = false;
$_SESSION['system_cache'] = true; /** now using Redis - this is in use */
$_SESSION['redis_cache'] = true;

$_SESSION['media_server'] = $beta ? 1 : 0;
$_SESSION['cloudinary']   = 0;
$_SESSION['host'] = ['protocol' => $host_protocol, 'sub' => $host_sub, 'domain' => $host_domain, 'tld' => $host_tld, 'port' => $host_port];
$_SESSION['host_tld'] = $host_tld;
$_SESSION['host_dom'] = $host_dom;
$_SESSION['host_sub'] = $host_sub;   

# live or dev/test/staging/beta/local ?
$_SESSION['dev'] = $dev = $host_sub == 'dev' ? 1 : 0;
$_SESSION['test'] = $test = $host_sub == 'test' ? 1 : 0;
$_SESSION['staging'] = $staging = $host_sub == 'staging' ? 1 : 0;
$_SESSION['local'] = $local = $host_sub == 'local' ? 1 : 0;
$_SESSION['beta'] = $beta = $host_sub == 'beta' ? 1 : 0;
$_SESSION['online'] = $online = $local ? env_is_online() : true; // if running locally, check if online, otherwise assume true
$_SESSION['offline'] = !$online; 
$_SESSION['aid'] = isset($_GET['_aid']) ? $_GET['_aid'] : $_SESSION['aid'];   

$live = $_SESSION['live'] = !($dev || $test || $beta || $staging || $local) ? 1 : 0; // www or no sub
$_SESSION['deployment'] = $live ? 'live' : $host_sub;
$_SESSION['send_mail'] = ['live' => 1, 'test' => 0, 'dev' => 0, 'staging' => 0, 'beta' => 0, 'local' => 0]; // whether to send if not live
if(!$_SESSION['live']) $version = $_SESSION['version'] = date('mdHis');
$_SESSION['log_db'] = !$_SESSION['live'] && isset($_GET['log_db']) ? 1 : 0;
$__header = ['end_scripts' => [], 'scripts' => [], 'styles' => []];


require_once("constants.inc");
require_once("class_constants.inc");
require_once("helpers.inc");
require_once("vendor/autoload.php");                          
require_once("auth/php/languages/en_GB.php");
$auth_lang = $lang; // $lang is included in file above. Do not delete this line.
require_once("auth/php/config.class.php");
require_once("auth/php/auth.class.php");

/** read config file */
$_SESSION['config'] = !$_SESSION['config'] || isset($_GET['reload-config']) ? config_load() : $_SESSION['config'];
$_SESSION['log_level'] = $_SESSION['system_log_level'] = env_log_level($deployment);

/** db */
require_once("PEAR.php");
require_once "Mail/RFC822.php";
require_once("db.inc");
require_once("classes.inc");
require_once("class_handlers.inc");
require_once("controllers.inc");
require_once("db_object.inc");

require_once("helpers_file.inc");
require_once("helpers_html.inc");
require_once("helpers_site.inc");
require_once("helpers_time.inc");
require_once("helpers_media.inc");
require_once("helpers_mail.inc");
require_once("helpers_google.inc");

/** if login */
require_once("db_user.inc");

/** only gallery sites */
require_once("helpers_gallery.inc");

/** only rental sites */
require_once("db_rental.inc");
require_once("db_booking.inc");
require_once("db_reservation.inc"); /** get rid of */
require_once("db_apartment.inc"); /** get rid of */
require_once("db_location.inc");

/** only if payment */
require_once("db_invoice.inc");
require_once("db_payment.inc");
require_once("db_rating.inc");

/** which site */
define('SITE_URL', siteURL());
if($_SESSION['siteObj']) {
  $siteObj = $_SESSION['siteObj'];
  $site_id = $siteObj->id;
} else {
  $site_id = $_SESSION['site_id'] = env_site_id($site_domain); /** inline switch */
  if(!$site_id) die("Don't know {$site_domain}");
  
  $siteObj = $_SESSION['siteObj'] = get_object('site', $site_id); /** uses Redis */
  // $__SITES = find_objects('site', ['client_id' => $__CLIENT_ID]); /** database lookup */
  $_SESSION['client_id'] = $siteObj->client_id; 
  $_SESSION['legal_id'] = $siteObj->legal_entity_id; 
  $_SESSION['site_url'] = SITE_URL; // will be http or https as needed
  $site_lang = $siteObj->default_language;
  $langs = $_SESSION['languages'] = json_decode($siteObj->languages) ?: [$siteObj->default_language];
}

/** site specific includes */
if($lib_prefix = $siteObj->library_prefix ?: $siteObj->shortname) {
  if(fileexists($lib_prefix."_classes.inc")) include_once($lib_prefix."_classes.inc");
  if(fileexists($lib_prefix."_class_handlers.inc")) include_once($lib_prefix."_class_handlers.inc");
  if(fileexists($lib_prefix."_class_constants.inc")) include_once($lib_prefix."_class_constants.inc");
  if(fileexists($lib_prefix."_helpers.inc")) include_once($lib_prefix."_helpers.inc");
  if(fileexists($lib_prefix."_controllers.inc")) include_once($lib_prefix."_controllers.inc");
  if(fileexists($lib_prefix."_cronscripts.inc")) include_once($lib_prefix."_cronscripts.inc");
}  

/** site specific directories */
$data_dir = $_SESSION['data_dir'] = $livw ? "/web/data/{$siteObj->shortname}/" : "/web/data-dev/{$siteObj->shortname}/"; 
$log_dir = $_SESSION['log_dir'] = $data_dir."log/";
$upload_dir = $_SESSION['upload_dir'] = $data_dir."upload/";
$cache_dir = $_SESSION['cache_dir'] = $data_dir."cache/";
if($_SESSION['test']) $cache_dir = $_SESSION['cache_dir'] = str_replace('/data-dev/', '/data/', $cache_dir);
$xml_dir = $data_dir."XML/";

$null = is_dir($data_dir) ?: mkdir($data_dir, 0700, true);
$null = is_dir($log_dir) ?: mkdir($log_dir, 0700, true);
$null = is_dir($cache_dir) ?: mkdir($cache_dir, 0700, true);


/** auth - login */
if($u_id = $_SESSION['u_id']) {
  $userObj = $__USER = get_user($u_id); 
  $u_level = $userObj->user_level;
} else {   
  $config = new PHPAuth\Config($db);
  $config->overrideAll($siteObj);
  $phpauth = new PHPAuth\Auth($db, $config, $auth_lang);
    
  $cookie_hash = $_COOKIE['authID'];
  $session_hash = $_SESSION['hash'];
  $auth_hash = $phpauth->getSessionHash();
  $hash = pick_first($session_hash, $auth_hash, $cookie_hash);
  
  $_SESSION['auth_debug'] = false; // $_SESSION['live'] ? false : true;

  if($provider_name = $_GET["provider"]) {
    /** hyridauth: version 2.8.2 */
    require_once('/web/comps/php/vendor/hybridauth/hybridauth-master/hybridauth/Hybrid/Auth.php'); #Hybridauth API
    require_once('/web/comps/php/vendor/hybridauth/hybridauth-master/vendor/autoload.php'); #Facebook API
    
    $user_id = user_provider_login($provider_name);
    $provider_login = $user_id ? true : false;
    if ($provider_login) {
      $result = $phpauth->third_party_login($user_id);
      $hash = $result['hash'];
    }
  }
    
  
  if($hash) {   
    $_SESSION['hash'] = $hash;
    $domain = $siteObj->domain;
    $is_logged = $phpauth->isLogged();
    $u_id = $_SESSION['u_id'];
    $auth_u_id = $phpauth->getSessionUID($hash);
    $valid = $phpauth->checkSession($hash);
    $u_id = $auth_u_id ?: $u_id;
    if ($u_id && $valid) {
      if($_GET['act']=="logout") { // Check for logout
        $phpauth->logout($hash);
        $_SESSION['loggedin'] = $_SESSION['userObj'] = $_SESSION['hash'] = $u = $u_level = $u_id = $u_addid = $u_personid = $u_type = $u_email = $userObj = NULL;
        session_destroy();
      } else {
        $_SESSION['loggedin'] = 1;
        
        $userObj = get_user($u_id); /** database lookup */
            
        if(!$userObj) die("no user $u_id");
        $upload_dir = $data_dir."user/"; // for all users
        $null = is_dir($upload_dir) ?: mkdir($upload_dir, 0700, true);
        $u_hostid = $userObj->user_level == USER_LEVEL_OWNER || user_has_role($userObj, USER_ROLE_OWNER) ? $u_id : 0;
        $_SESSION['root_user'] =  $u_id == SYSTEM_USER_ID ? 1 : 0;  
        $u_level = $u['user_level'] = $_SESSION['user_level'] = $userObj->user_level;
        $u = obj2array($userObj);
        $_SESSION['userObj'] = $userObj;
        $_SESSION['u_id'] = $_SESSION['user_id'] = $u_id;
      }
    } else {
      $_SESSION['loggedin'] = $_SESSION['userObj'] = $_SESSION['hash'] = $u = $u_level = $u_id = $u_addid = $u_personid = $u_type = $u_email = $userObj = NULL;
    }
  }
  
  if($provider_login && $_GET['redirect']) {
    redirect($_GET['redirect']);
  }
  
}
   
/** gets set to Europe/Amsterdam somewhere above... */
// set System Timezone to UTC
if(date_default_timezone_get() != SYSTEM_TIMEZONE) {
  date_default_timezone_set(SYSTEM_TIMEZONE); // UTC: Also set MySQL?
}


  
/** global scope, all pages */
$global = new stdClass; /** data passed to app */
/** end global scope */


/** store site globals */
$__GLOBAL = $_SESSION['global_scope'] = $global;
$__LIVE   = $_SESSION['live'];
$__TEST   = $_SESSION['test'];
$__DEV    = $_SESSION['dev'];
$__CLIENT_ID = $_SESSION['client_id'];
$__APP_ROOT = $_SESSION['app_root'] = $app_root;
$__DOC_ROOT = $doc_root;

$__USER   = $userObj;
$__SITE   = $siteObj;
$__PAGE   = $pageObj;
$__SITE_ID = $siteObj->id;

$__LOCAL_TEMPLATE = 0; // set to 1 if the smarty template is local to this site
$__TEMPLATE = $__TEMPLATE_PATH = '';
$__AUTH_EDIT = $u_level >= USER_LEVEL_STAFF; // allowed to edit using CMS
$__EDIT_MODE = $_SESSION['__edit_mode'];
$__LANG = $__LANGUAGE = $_SESSION['language'];
$__LANGS = $__LANGUAGES = $_SESSION['languages'];
$__DEPLOYMENT = $_SESSION['deployment'];
$__USER_CURRENCY = $_SESSION['user_currency'] = 'EUR'; /** todo: make configurable by user */
$__USER_LEVELS = [USER_LEVEL_USER => 'Member', USER_LEVEL_EDITOR => 'Editor', USER_LEVEL_STAFF => 'Staff'];

$__PATH_VAR = $_SESSION['path_var'];
$__DEFAULT_BOUNDS = '[["28.4371","-16.0021"],["74.6767","41.6541"]]';

$gapi_key = "AIzaSyDqzndmgSgkwaD6AEATZOkeEWUo4foizEo";
define("GMAP_API", "https://maps.googleapis.com/maps/api/js?key={$gapi_key}&libraries=places&language={$__LANG}&v=3.26");

$_SESSION['send_mail']['test'] = 0; 
if($client_ip == '213.93.144.196') {
  $_SESSION['send_mail']['test'] = 'test@kjakman.com'; 
  $_SESSION['send_mail']['dev'] = 'dev@kjakman.com';
}
