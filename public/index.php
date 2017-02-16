<?php

require("set_env.inc"); /** todo: get rid of */

/** new index.php inspired by 
  https://nathandavison.com/article/10/custom-php-mvc-tutorial-part-2-url-mapping-and-indexphp
*/

//require the general classes
require("classes/Application.php");
require("classes/Router.php");
require("classes/Model.php");
require("classes/View.php");
require("classes/BaseController.php");

load_dependencies(); // load dependencies into global $__header variable
$app = new AFR\Application($__SITE, $__USER); //create the controller and execute the action
$app->run(); // run the app


/** todo: move the basics to index.html, load rest when needed. Use grunt to combine/minify */
function load_dependencies() {  
  global $__header, $u_id, $u_level, $__SITE, $__LANG;
  $ver = $_SESSION['version'] ?: date('md');
  $siteObj = $__SITE;
  $lang = $__LANG ?: $__SITE->default_language;

  $__header['css'][] = "/afr/css/afr_base.css?v=$ver";  
  $__header['css'][] = "/afr/css/afr_rental.css?v=$ver";  
  $__header['css'][] = "/afr/css/afr_tooltip.css";
  $__header['css'][] = "/afr/css/google_pac.css"; 
  
  if($u_id) $__header['css'][] = "/afr/css/afr_cms.css?ver=$ver";
  if(is_file($_SERVER['DOCUMENT_ROOT']."/css/site_".$siteObj->shortname.".css")) $__header['css'][] = "/css/site_".$siteObj->shortname.".css";
  $__header['css'][] = "//fonts.googleapis.com/css?family=Roboto:400,300,100,500,700";
  $__header['css'][] = "//fonts.googleapis.com/css?family=Open+Sans:400italic,400,300,600";
  $__header['css'][] = "//maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css";
  $__header['css'][] = "/afr/font/afr/styles.css";
  
  /** traveler */
  $__header['css'][] = "/traveler/css/icomoon.css";
  $__header['css'][] = "/traveler/css/styles.css?v=$ver";
  $__header['css'][] = "/traveler/css/mystyles.css?v=$ver";
   
  $__header['css'][] = "/afr/bower/fancybox/source/jquery.fancybox.css";
  $__header['css'][] = "/afr/bower/summernote/dist/summernote.css";   
  $__header['css'][] = "/afr/bower/bootstrap3-wysihtml5-bower/dist/bootstrap3-wysihtml5.min.css";
  $__header['css'][] = "/afr/bower/bootstrap-toggle/css/bootstrap-toggle.min.css";
  $__header['css'][] = "/afr/bower/bootstrap-modal/css/bootstrap-modal-bs3patch.css";
  $__header['css'][] = "/afr/bower/bootstrap-modal/css/bootstrap-modal.css";
  $__header['css'][] = "https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.4/css/bootstrap-datepicker3.min.css";
  
  $__header['css'][] = "/afr/bower/ionrangeslider/css/ion.rangeSlider.css";
  $__header['css'][] = "/afr/bower/bootstrap-star-rating/css/star-rating.css";
  $__header['css'][] = "/afr/bower/select2/select2.css";    
  $__header['css'][] = "/afr/bower/flag-icon-css/css/flag-icon.min.css";    
  $__header['css'][] = "/afr/bower/bootstrap-social/bootstrap-social.css";    
  $__header['css'][] = "/afr/bower/intl-tel-input/build/css/intlTelInput.css"; /* Note: must set .iti-flag {background-image: url("/bower/intl-tel-input/build/img/flags.png");} in css */    
  $__header['css'][] = "/afr/bower/magnific-popup/dist/magnific-popup.css";  
  $__header['css'][] = "/afr/bower/addtocalendar/atc.css";
    
  // top scripts
  $__header['base_scripts'][] = "/afr/bower/jquery/dist/jquery.min.js"; // these are loaded first
  $__header['base_scripts'][] = "/afr/bower/jquery-ui/ui/minified/jquery-ui.min.js";

  // moment + moment-range, using node
  $__header['base_scripts'][] = "/afr/node/moment/moment.js";    
  $__header['base_scripts'][] = "/afr/node/moment-range/dist/moment-range.js";
  $__header['base_scripts'][] ="script:window['moment-range'].extendMoment(moment)";
  
  if($lang !== 'en') $__header['base_scripts'][] = "/afr/bower/moment/locale/{$lang}.js";
  
  $__header['base_scripts'][] = "https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.6.4/js/bootstrap-datepicker.min.js";
  $__header['base_scripts'][] = "//maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js";
  $__header['base_scripts'][] = "https://use.fontawesome.com/a22cbf3bb2.js";
  $__header['base_scripts'][] = "/afr/js/afr.js?v=$ver";
  if($u_id) $__header['base_scripts'][] = "/afr/js/afr_cms.js?v=$ver";

  if($siteObj->property_site || $siteObj->property_type) $__header['base_scripts'][] = "/afr/js/afr_rental.js?v=$ver";

  $__header['base_scripts'][] = GMAP_API;
  $__header['base_scripts'][] = "https://cdn.rawgit.com/googlemaps/v3-utility-library/master/markerwithlabel/src/markerwithlabel.js";  
  $__header['base_scripts'][] = "/afr/js/google_pac.js?v=$ver";  
  $__header['base_scripts'][] = "/afr/bower/fancybox/source/jquery.fancybox.pack.js";
  $__header['base_scripts'][] = "/afr/bower/summernote/dist/summernote.min.js";
  $__header['base_scripts'][] = "/afr/bower/bootstrap3-wysihtml5-bower/dist/bootstrap3-wysihtml5.all.min.js";  

  // end scripts
  $__header['end_scripts'][] = "/js/main.js?v=$ver";

  /** traveler */
  $__header['end_scripts'][] = "/traveler/js/slimmenu.js";
  $__header['end_scripts'][] = "/traveler/js/nicescroll.js";
  $__header['end_scripts'][] = "/traveler/js/dropit.js";
  $__header['end_scripts'][] = "/traveler/js/icheck.js";
  $__header['end_scripts'][] = "/traveler/js/fotorama.js";
  $__header['end_scripts'][] = "/traveler/js/typeahead.js";
  $__header['end_scripts'][] = "/traveler/js/card-payment.js";
  $__header['end_scripts'][] = "/traveler/js/owl-carousel.js";
  $__header['end_scripts'][] = "/traveler/js/fitvids.js";
  $__header['end_scripts'][] = "/traveler/js/tweet.js";
  $__header['end_scripts'][] = "/traveler/js/gridrotator.js";  
  $__header['end_scripts'][] = "/afr/bower/magnific-popup/dist/jquery.magnific-popup.min.js";
  $__header['end_scripts'][] = "/afr/bower/select-to-autocomplete/jquery.select-to-autocomplete.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-validator/dist/validator.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-confirmation2/bootstrap-confirmation.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-toggle/js/bootstrap-toggle.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-modal/js/bootstrap-modalmanager.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-modal/js/bootstrap-modal.js";
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
  $__header['end_scripts'][] = "/afr/bower/zeroclipboard/dist/ZeroClipboard.min.js";  
  $__header['end_scripts'][] = "/traveler/js/custom.js?v=$ver";    

  if($auth_edit) {
    $__header['css'][] = "/afr/bower/CodeMirror/lib/codemirror.css"; 
    $__header['end_scripts'][] = "/afr/bower/CodeMirror/lib/codemirror.js"; 
    $__header['end_scripts'][] = "/afr/bower/CodeMirror/mode/smarty/smarty.js"; 
  }
  if($siteObj->google_tag_id) $__header['end_scripts'][] = "/afr/js/lunametrics.js?v=$ver"; 
}
