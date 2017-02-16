<?php

function google_branding($id='google_branding') {
  if(!$id) return;
  $out = html_div('', '', "id='$id'");
  $out .= html_script_inline("google.load('language', '1');google.language.getBranding('$id')");
  return $out;
}

function google_plusone_script($options=NULL) {
  return "(function() {
    var po = document.createElement('script'); po.type = 'text/javascript'; po.async = true;
    po.src = 'https://apis.google.com/js/plusone.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(po, s);
  })();";
}

function google_plusone($options=NULL) {
  global $__header;
  $size = $options['size'] ?: 'medium';
  $button = "<div class=\"g-plusone\" data-size=\"$size\" data-annotation=\"none\"></div>";
  //$button = "<g:plusone size=\"$size\"></g:plusone>\n";
  if($options['async']) {
    $button .= html_script_inline(google_plusone_script());
  } else {
    $__header['scripts'][] = "https://apis.google.com/js/plusone.js";
  }
  return $button;
  return html_span($button, 'down-3px-cont');
}

function pinterest_pinit($url, $media, $description = '', $options=NULL) {
  if(!$url || !$media) return '';
  global $__header;
  $__header['end_scripts'][] = "//assets.pinterest.com/js/pinit.js";  
  $url = rawurlencode(add_http($url));
  $media = rawurlencode(add_http($media));
  if($description) $description = rawurlencode($description);
  $button = "<a href=\"http://pinterest.com/pin/create/button/?url=$url&media=$media&description=$description\" class=\"pin-it-button\" count-layout=\"horizontal\"><img border=\"0\" src=\"//assets.pinterest.com/images/PinExt.png\" title=\"Pin It\" /></a>";
  return $button;
  return html_span($button, 'down-3px-cont');
}

function google_timezone($lat, $lng, $ts='') {
  if(!$ts) $ts = time();
  $url = "https://maps.googleapis.com/maps/api/timezone/json?location={$lat},{$lng}&timestamp={$ts}&key=YOUR_API_KEY";
  $url = "https://maps.googleapis.com/maps/api/timezone/json?location={$lat},{$lng}&timestamp={$ts}";
  $json = get_html($url);
  $result = json_decode($json);
  
  if($full = $options['full']) return $result;

  return $result;
  
  $status = $result->status;
  $results = $result->results;
  $last = array_pop($results);
  return $status == 'OK' ? parse_geometry($last->geometry) : array();

}

function google_geocode($address, $options=array()) {
  $q=urlencode($address);
  if(isset($options['sensor'])) {
    $sensor = $options['sensor'] ? 'true' : 'false';
  } else {
    $sensor = 'false';
  }
  $url = "https://maps.googleapis.com/maps/api/geocode/json?address=$q&sensor=$sensor";
  $json = get_html($url);
  $result = json_decode($json);
  
  if($full = $options['full']) return $result;

  $status = $result->status;
  $results = $result->results;
  $last = array_pop($results);
  return $status == 'OK' ? parse_geometry($last->geometry) : array();
}

function parse_geometry($geo) {
  $lat = $geo->location->lat;
  $lng = $geo->location->lng;
  $bounds = $geo->bounds ?: $geo->viewport;
  $bounds_json = $bounds ? json_encode($bounds) : '';
  return array(200, $geo->location_type, $lat, $lng, $bounds_json);
}

// move to helpers_twitter.inc
function twitter_script($options=NULL) {            
  return'<script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?"http":"https";if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+"://platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document, "script", "twitter-wjs");</script>';
}

//function twitter_script() {
// return "!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0];if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=\"https://platform.twitter.com/widgets.js\";fjs.parentNode.insertBefore(js,fjs);}}(document,\"script\",\"twitter-wjs\");";
//}

function twitter_share_button($tweetData, $options=NULL) {  
  if(is_array($tweetData)) foreach($tweetData as $key => $value) $options['data-'.$key] = $value;
  //if(!isset($options['class'])) $options['class'] = ' twitter-share-button';
  $options['class'] .= ' twitter-share-button';
  $name = isset($options['name']) ? $options['name'] : "Tweet";
  //$name = 'foo';
  $output = html_link("https://twitter.com/share", $name, $options);
  //$output .= twitter_script();
  return $output;
}


function twitter_tweet($url, $tweet, $options=NULL) {
  if(!$tweet) return '';
  global $__header;
  //$__header['end_scripts'][] = twitter_script();  
  $__header['end_scripts'][] = "https://platform.twitter.com/widgets.js";  
  
  $tweet = rawurlencode($tweet);
  $url = rawurlencode(add_http($url));
  $button = "<a href=\"http://twitter.com/share?text=$tweet&url=$url&related=$related\" class=\"twitter-share-button\" data-count=\"none\" target=\"_blank\" rel=\"nofollow\">Tweet</a>";
  return $button;
}

// wrapper for call to some Google API v2
// supported methods: translate, detect
// if full_result is true, whole struct is returned
// max 2K for get, 5K for POST


function google_api_post($method, $fields, $options=NULL) {
  $errors = array();
  if(!$_SESSION['google_app_api_key']) die("google_api_post: missing app key");
  $fields['key'] = $_SESSION['google_app_api_key'];  
  $url = "https://www.googleapis.com/language/translate/v2/$method";
  //$url = "http://dev.apartments-for-rent.com/home/tmp2.php";

  if($options['get']) { // use GET, 2k max
    $params = array2qs($fields);
    $url .= "?$params";
    list($json_result, $status) = get_html_and_status($url);
  } else {  // post is default - 5k max
    $curl_options[CURLOPT_HTTPHEADER] = array('X-HTTP-Method-Override: GET');
    list($json_result, $status) = http_post($url, $fields, $curl_options, array('get_status' => true));
  }  
  
  $result = json_decode($json_result);
  $text = $options['full_result'] ? $result : '';
  if(!$result->error && $status == 200) {
    if(!$options['full_result']) {
      $translations = $result->data->translations;
      $text = $translations[0]->translatedText; 
    }
  } else {
    echo(html_break()."Error from google_api_post: method = $method");
    dump($result);
    dump($fields);
    if($result->error) {
      $errors[] = $result->error->code.": ".$result->error->message;
      die();
    } else {
      $errors[] = "google_api_post: $url returned status $status";
    }
  }
  
  return array($text, $errors);
}  
  // old code (v1)
  /*  
  $url = "http://ajax.googleapis.com/ajax/services/language/".$method; // default to this URL
  $http_method = 'GET'; // default to GET
  switch($method) {
    case 'translate':    
      $result_field = 'translatedText';
      $http_method = 'POST';
      break;
    case 'detect':    
      $result_field = 'language';
      break;
    default:
      die("google_api_post: unknown method $method");    
  }
  $max_length = $http_method == 'POST' ? 5000 : 500; // really 5000: this according to http://code.google.com/apis/ajaxlanguage/terms.html (is really 5000)
  $term = trim($fields['q']);  
  if(!$term) return '';  
  $len = strlen($term);
  if($len > $max_length) {
    // echo("<b>Google $method warning</b> term is $len bytes. Truncating to $max_length<br>");
    $term = substr($term, 0, $max_length);
  } 
  $fields['v'] = $version;
  $fields['userip'] = $_SERVER['REMOTE_ADDR'];
  $fields['key'] = $_SESSION['google_api_key']; 
  if($http_method == 'POST') { // POST the data
    $fields['q'] = $term;
    $options[CURLOPT_REFERER] = $_SERVER['HTTP_HOST'];  
    $response = http_post($url, $fields, $options);
  } else { // use GET
    $fields['q'] = substr(urlencode($term), 0, $max_length);
    $url = $url.'?'.array2qs($fields, false);
    $response = get_html($url);
  }

  $result = json_decode($response);
  //dump($result);

  if($result->responseStatus == '200') {
    
    return $full_result ? $result : $result->responseData->$result_field;
  } else {
     echo("<b>Google $method error</b> from $url<br>");
     dump($response);
     if(is_object($result)) dump($result);
     die();
     return false;
  }
*/

// format can be 'text' or 'html'
// max 2K for get, 5K for POST
function google_translate($term, $to_lang, $from_lang= '', $options=NULL) {
  $org_term = $term;
  $term = trim($term);
  if(!$term) return array('', array("google_translate: missing term for term=$term org='$org_term'"));
  if($options['html']) { // html  
    $method = 'html';
    $fields['q'] = $q = preg_replace('!\s+!', ' ', $term);
    $len = strlen(strip_tags($q));
  } else { // text - default 
    $method = 'text';
    $fields['q'] = $q = strip_tags($term); // remove tags
    $len = strlen($q);
  }
  if(!$len) return array('', array("google_translate: missing len for term=$term org='$org_term'"));
  if(!$to_lang) return array('', array("google_translate: missing to_lang for term=$term"));
  $max = $options['get'] ? 2000 : 5000;
  if($len > $max) {
    return array('', array("google_translate: input too long $len > $max"));
  }
  
  if($from_lang) $fields['source'] = $from_lang;
  $fields['target'] = $to_lang;
  $fields['format'] = $options['format'] ?: 'text'; // text or html
  list($text, $errors) = google_api_post('translate', $fields, $options);
  //echo("Google: t='$term' q='$q' result='$text' m=$method<br>");
  //die();
  return array($text, $errors);
}    

// detect language in a string
function google_detect($term, $full_result=false) {
  $fields['q'] = str_replace('  ', ' ', $term); // remove double spaces
  return google_api_post('detect', $fields, $full_result);
}    

// old translate code
//  $len = strlen($term);
//  if(!$len) return "";
//  //echo("google translate: $len bytes from $from_lang to $to_lang<br>");
//  $translator = new googleTranslateTool($from_lang, $to_lang);
//  $ttt = str_replace(array('__', '_'), array('xxvarxx', ' '), $term);
//  $result = $translator->translate_Text($ttt);
//  usleep(rand(0,100000)); // wait fraction of a tenth of a second
//  if($delay) usleep(rand(0,1000000)); // wait fraction of a second
//  if($result===false) {
//    echo("<b>GT error</b><br>");
//    dump($result);
//    return false;
//  } else {
//
//    //analyze($result);
//    $utf = $result;
//    return str_replace(array('&lt;','&gt;','xxvarxx'), array('<','>','__'), $utf);
//  }
//}


function google_tracker($acct) {
  return $acct ? "<script>
  (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  })(window,document,'script','//www.google-analytics.com/analytics.js','ga');
  ga('create', '$acct', 'auto');
  ga('send', 'pageview');
  //ga('require', 'ecommerce');   
  ga('require', 'ecommerce', 'ecommerce.js');   // Load the ecommerce plug-in.
  </script>" : '';
}



function display_referral_ad() {
	return "";
  $lang = $_SESSION['language'] ? $_SESSION['language'] : 'en';
  echo("
  <script type='text/javascript'><!--
  google_ad_client = 'pub-6293044799390826';
  google_ad_width = 180;
  google_ad_height = 60;
  google_ad_format = '180x60_as_rimg';
  google_cpa_choice = 'CAEQhan8zwEaCOgpeb50aXvYKMu293M';
  google_language = '$lang';
  //-->
  </script>
  <script type='text/javascript' src='http://pagead2.googlesyndication.com/pagead/show_ads.js'>
  </script>
  ");
}

function display_ad_slot($slot, $echo=false) {
	return "";
  global $u;
  if($u || $_SESSION['dev']) return "";
  $lang = $_SESSION['language'] ? $_SESSION['language'] : 'en';
  switch($slot) {
   case "1376205948":
    $w=200;$h=90;break; //link unit
   case "6928533474":
    $w=160;$h=600;break; //text only
   case "5862122940":
    $w=200;$h=200;break; // mixed
   case "3174885258":
    $w=200;$h=200;break; // image only
   case "3165648612":
    $w=336;$h=280;break; // mixed
   case "5175816620":
    $w=728;$h=90;break; // mixed
   case "4641992153":
    $w=728;$h=90;break; // text only
   default:
    $w=160;$h=600;break;
   }

  $ad = <<<EOF
<script type="text/javascript"><!--
google_ad_client = "pub-6293044799390826";
/* $wx$h, created 2/7/08 */
google_ad_slot = "$slot";
google_ad_width = $w;
google_ad_height = $h;
//-->
</script>
<script type="text/javascript"
src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
</script>
EOF;
  if($echo) echo($ad); else return $ad;
}

function display_ad($type, $w, $h, $channel='', $colors='') {
	return "";
  global $host_protocol;
  if($host_protocol=='https') return ""; // don't show ads on secure pages
  if($_SESSION['no_ads']) return "";
// $type can be: link, text, images, text_image

// ad_format: WxH_format
// format: as = text + img
// valid sizes (w x h):

// text + image: "728x90","468x60","120x600","160x600","336x280","300x250","250x250","200x200"
//  google_ad_type = "text_image";

// image only: "728x90", "468x60", "234x60", "120x600", "160x600", "120x240", "336x280", "300x250", "250x250", "200x200", "180x150", "125x125"
//  google_ad_type = "image";

// text only: "728x90", "468x60", "234x60", "120x600","160x600","120x240","336x280","300x250","250x250","200x200","180x150","125x125"
//  google_ad_type = "text";

// link only: "728x15","468x15","200x90","180x90","160x90","120x90",
// google_ad_format = "728x15_0ads_al";

  $dark='
    google_color_border = "A56B08";
    google_color_bg = "181018";
    google_color_link = "DDDDDD";
    google_color_text = "CDCDCD";
    google_color_url = "DDDDDD";
';

  $light ='
    google_color_border = "f7bf01";
    google_color_bg = "4c4c4c";
    google_color_link = "f7bf01";
    google_color_text = "FFFFFF";
    google_color_url = "f7bf01";
';

  $light2 ='
    google_color_border = "f7bf01";
    google_color_bg = "ffffff";
    google_color_link = "f7bf01";
    google_color_text = "4c4c4c";
    google_color_url = "f7bf01";
';

  $white ='
    google_color_border = "cccc0c";
    google_color_bg = "CECBCE";
    google_color_link = "634208";
    google_color_text = "000000";
    google_color_url = "9c1021";
';

  if($colors=='light') {
    $color_str =$light;
  } elseif($colors=='light2') {
    $color_str =$light2;
  } elseif($colors=='dark') {
    $color_str =$dark;
  } elseif($colors=='white') {
    $color_str =$white;
  } else {
    $color_str =$light;
  }


switch($channel) {

  case 'centerlink':
  $channel_str ='
  //2007-02-21: afr, centerlink
  google_ad_channel = "3913846171+1164510021";
';
  break;

  case 'centertext':
  $channel_str ='
  //2007-02-21: afr, centertext
  google_ad_channel = "3913846171+2524305736";
';
  break;

  case 'righttext':
  $channel_str ='
  //2007-02-21: afr, righttext
  google_ad_channel = "3913846171+6174730519";
';
  break;

  case 'lefttext':
  $channel_str ='
  //2007-02-21: afr, lefttext
  google_ad_channel = "3913846171+1823288499";
';
  break;

  case 'bottomlink':
  $channel_str ='
  //2007-02-21: afr, bottomlink
  google_ad_channel = "3913846171+5844466352";
';
  break;

  case 'leftimage':
  $channel_str ='
  //2007-02-21: afr, bottomlink
  google_ad_channel = "3913846171+8638344940";
';
  break;

  case 'mas':
  $channel_str ='
  //2007-02-21: afr, mas
  google_ad_channel = "3913846171+2679119405";
';
  break;

  default:
  $channel_str ='
  //2007-02-21: afr
  google_ad_channel = "3913846171";
';
  break;
}

if($type=='link') {
  $ad_type = "";
  $ad_format = 'google_ad_format = "'.$w.'x'.$h.'_0ads_al";';
} else {
  $ad_type = 'google_ad_type = "'.$type.'";';
  $ad_format = 'google_ad_format = "'.$w.'x'.$h.'_as";';
}

  echo("
  <script type=\"text/javascript\"><!--
  google_ad_client = \"pub-6293044799390826\";
  google_ad_width = $w;
  google_ad_height = $h;
  $ad_format
  $ad_type
  $channel_str
  $color_str
  //--></script>
  <script type=\"text/javascript\"
    src=\"http://pagead2.googlesyndication.com/pagead/show_ads.js\">
  </script>
  ");

}                                                           

// see: http://www.stylifyyourblog.com/2011/07/customize-google-custom-search-box.html
function google_search($siteObj, $id, $options=NULL) {
  global $__header;
  $width = $options['width'] ?: '100%';
  if(isint($width)) $width .= 'px';
  $theme = $options['theme'] ?: 'MINIMALIST';
  $action = site_pagetype_link($siteObj, PAGE_SEARCH);
  // $output = '<div id="cse" style="width: '.$width.';">Loading</div>';
  $__header['scripts'][] = '//www.google.com/jsapi';
  //$__header['scripts'][] = '/afr/js/google_jsapi.min.js';
  $__header['css'][] = $options['css'] ?: '/afr/css/google_search.css';
  $output .= '
    <form id="searchbox_'.$id.'" action="'.$action.'">
      <input value="'.$id.'" name="cx" type="hidden"/>
      <input value="FORID:11" name="cof" type="hidden"/>
      <input id="q" style="width:'.$width.';" name="q" size="70" type="text" />
      <input value="Search" name="sa" type="submit"/>
    </form>
    ';  
  return html_div($output, '', "id='google_search'");      
}


// valid themes: BUBBLEGUM, ESPRESSO, GREENSKY, MINIMALIST, SHINY            
function google_search_std($id, $options=NULL) {
  global $__header;
  $width = $options['width'] ?: '100%';
  if(isint($width)) $width .= 'px';
  $theme = $options['theme'] ?: 'MINIMALIST';
  $output = '<div id="cse" style="width: '.$width.';">Loading</div>';
  $__header['scripts'][] = '//www.google.com/jsapi';
  $__header['css'][] = $options['css'] ?: '/afr/css/google_search.css';
  $output .= html_script_inline("
  google.load('search', '1', {style : google.loader.themes.".strtoupper($theme)."});
  google.setOnLoadCallback(function() {
    var customSearchOptions = {};  var customSearchControl = new google.search.CustomSearchControl(
      '$id', customSearchOptions);
    customSearchControl.setResultSetSize(google.search.Search.FILTERED_CSE_RESULTSET);
    customSearchControl.draw('cse');
  }, true);
    ");  
  return $output;      
}


function display_google_search($lang='en') {
  if(!$_SESSION['show_search']) return '';

  $domain = $_SERVER['HTTP_HOST'];
  return ('
<div id="sitesearch">
<!-- SiteSearch Google -->
<form method="get" action="http://'.$server.'/search/">
<table border="0" bgcolor="#f3f3f3">
<tr><td style="white-space: nowrap;" valign="top" align="left" height="32">

<input type="hidden" name="domains" value="'.$server.'"></input>
<label for="sbi" style="display: none">Enter your search terms</label>
<input type="text" name="q" size="31" maxlength="255" value="" id="sbi"></input>
<label for="sbb" style="display: none">Submit search form</label>
<input type="submit" name="sa" value="Google Search" id="sbb"></input>
</td></tr>
<tr>
<td style="white-space: nowrap;" >
<table>
<tr>
<td>
<input type="radio" name="sitesearch" value="" checked id="ss0"></input>
<label for="ss0" title="Search the Web"><font size="-1" color="#000000">Web</font></label></td>
<td>
<input type="radio" name="sitesearch" value="'.$server.'" id="ss1" CHECKED></input>
<label for="ss1" title="Search '.$server.'"><font size="-1" color="#000000">'.$server.'</font></label></td>
</tr>
</table>
<input type="hidden" name="client" value="pub-6293044799390826"></input>
<input type="hidden" name="forid" value="1"></input>
<input type="hidden" name="channel" value="4784782340"></input>
<input type="hidden" name="ie" value="UTF-8"></input>
<input type="hidden" name="oe" value="UTF-8"></input>
<input type="hidden" name="safe" value="active"></input>
<input type="hidden" name="flav" value="0000"></input>
<input type="hidden" name="sig" value="8FzbI7Kl9ubTtibG"></input>
<input type="hidden" name="cof" value="GALT:#F7BF01;GL:1;DIV:#AEAEAE;VLC:F7BF01;AH:center;BGC:F4F4F4;LBGC:F3F3F3;ALC:3E78A6;LC:3E78A6;T:000000;GFNT:0000FF;GIMP:0000FF;LH:50;LW:132;L:http://www.apartments-for-rent.com/images/old/logo_384.png;S:http://www.apartments-for-rent.com/;FORID:11"></input>
<input type="hidden" name="hl" value="'.$lang.'"></input>
</td></tr></table>
</form>
<!-- SiteSearch Google -->
</div>
');
}

function display_google_search_result($width='680', $lang='en') {
  return ("
<!-- Google Search Result Snippet Begins -->
<div id=\"googleSearchUnitIframe\"></div>

<script type=\"text/javascript\">
   var googleSearchIframeName = 'googleSearchUnitIframe';
   var googleSearchFrameWidth = ".$width.";
   var googleSearchFrameborder = 2 ;
   var googleSearchDomain = 'www.google.com';
</script>
<script type=\"text/javascript\"
         src=\"http://www.google.com/afsonline/show_afs_search.js\">
</script>
<!-- Google Search Result Snippet Ends -->
");
}

function get_google_key($domain) {
  $url = "http://www.google.com/maps/api_signup?url=".add_http($domain);
  $result = google_login('dummy@kjakman.com', 'dummy123', $url); 
  $key = find_delimited_str($result, '<p>Your key is:</p><pre class="code">', '</pre>');
  return $key;  
}

// logs in to google using dummy account, fetches $url and returns it  
function google_login($username, $password, $url) {
  // Uncomment to only allow from IP 1.1.1.1
  // if($_SERVER['REMOTE_ADDR'] !== '1.1.1.1') die();
  $username=urlencode($username);

  $gacookie="/web/cache/gcookie/";
  if(!is_dir($gacookie) &&!mkdir_recursive($gacookie)) {echo("google_login: failed to make dir $gacookie");return false;}
  $postdata="Email=$username&Passwd=$password&GA3T=5AS_gBsvDHI&nui=15&fpui=3&askapache=http://www.askapache.com/"
  ."&service=adsense&ifr=true&rm=hide&itmpl=true&hl=en_US&alwf=true&continue=$url&null=Sign in";
  $ch = curl_init();
  curl_setopt ($ch, CURLOPT_URL,"https://www.google.com/accounts/ServiceLoginBoxAuth");
  curl_setopt ($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_setopt ($ch, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.6) Gecko/20070725 Firefox/2.0.0.6");
  curl_setopt ($ch, CURLOPT_TIMEOUT, 60);
  curl_setopt ($ch, CURLOPT_FOLLOWLOCATION, 1);
  curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt ($ch, CURLOPT_COOKIEJAR, $gacookie);
  curl_setopt ($ch, CURLOPT_COOKIEFILE, $gacookie);
  curl_setopt ($ch, CURLOPT_REFERER, $url);
  curl_setopt ($ch, CURLOPT_POSTFIELDS, $postdata);
  curl_setopt ($ch, CURLOPT_POST, 1);
  $result = curl_exec ($ch);

  curl_setopt($ch, CURLOPT_URL,$url);
  $result = curl_exec ($ch);

  curl_close($ch);
  unlink($gacookie);
  return $result;
}  

/**
// returns an appropirate icon given an object type or landmark type
function gmap3_icon($obj_type, $options=NULL) {
  switch($obj_type) {
    case 'shortstay':
      $file = 'accommodation_hotel';
      break;
    case 'longstay':
      $file = '';
      break;
    case 'realestate':
      switch($options['type']) {
      default:       
        $file = '';
        break;
      }
      break;        
    case 'office':
      $file = '';
      break;
    case 'hotel':
      $file = 'hotel2';
      break;
    case 'boat':
      $file = 'transport_port';
      break;
    case 'airport':
      $file = 'transport_airport';
      break;
    case 'golf_district':
      $file = 'sport_golf';
      break;
    case 'golf_club':
      $file = 'sport_golf';
      break;
    case 'golf_course':
      $file = 'sport_golf';
      break;
      
    case 'landmark':
      switch($options['type']) {
      case LANDMARK_TYPE_ATTRACTION:
        $file = 'tourist_theme_park';
        break;
      case LANDMARK_TYPE_PARK:
        $file = 'tourist_fountain';
        break;
      case LANDMARK_TYPE_TRANSPORT:
        $file = 'transport_bus_stop';
        break;
      case LANDMARK_TYPE_ACCOMMODATION:
        $file = 'accommodation_hotel2';
        break;
      case LANDMARK_TYPE_RESTAURANT:
        $file = 'food_restaurant';
        break;
      case LANDMARK_TYPE_BAR:
        $file = 'food_bar';
        break;
      case LANDMARK_TYPE_VENUE:
        $file = 'tourist_theatre';
        break;
      case LANDMARK_TYPE_BOARDING:
        $file = 'transport_marina';
        break;
      case LANDMARK_TYPE_PLACE:
        $file = 'tourist_information';
        break;
      default:       
        $file = 'tourist_information';
        break;
      }
      break;        
    default:       
      $file = '';
      break;
  }
  if(!$file) {
    $file = $options['highlight'] ? 'pushpin_yellow' : 'pushpin_red';
    return "/images/map-icons/png/$file.p.32.png"; // we don't have other sizes yet
  }
  
  $ver = $options['positive'] ? 'p' : 'n'; // negative or positive
  $size = $options['highlight'] ? 24 : 16;
  return "/images/map-icons/png/$file.$ver.$size.png";
}


function gmap3($options=NULL) {
  global $__header;
  if($_SESSION['gmap_loaded']){
    //die("gmap loaded"); 
  } else {
  }
  $__header['scripts'][] = GMAP_API; // "//maps.google.com/maps/api/js?sensor=false";

  //$__header['scripts'][] = "/jquery/gmap/jquery.ui.map.full.min.js";

  $__header['scripts'][] = "/afr/bower/jquery-ui-map/ui/min/jquery.ui.map.full.min.js";
  $__header['scripts'][] = "/afr/js/afr_gmap.js";
  $id = $options['id'] ?: 'gmap';
  $class = $options['class']; // ?: 'gmap';
  $height = $options['height'] ?: 0;
  $width = $options['width'] ?: 0;
  if($height && $width) {
    $style = style_string($height, $width);
  }
  $init = isset($options['init']) ? $options['init'] : true;

  //$stack = caller_stack();
  //$onload = "  <!-- gmap3 -->\n";
  //if($search = $options['search']) $onload .= "  var search=".json_encode($search).";\n";
  //$onload .= "  gmap_icon = '/images/markers/pushpin_red.png';
  //gmap_icon_hi = '/images/markers/pushpin_yellow.png';\n
  //var id = '$id';\n
  //var len = $('#' + id).length;\n";

  if($init) {
    $accuracy = $options['accuracy'];    
    if($accuracy && ! $options['zoom']) $options['zoom'] = acc2zoom($accuracy);
    $onload = "var map_options={};map_options.id='$id';\n";
    if($markers = $options['markers']) {
      $onload .= gmap3_markers($options);
      $onload .= "map_options.markers = markers;\n";
    }
      //"markers = map_options.markers = ".json_encode(is_array($markers) ? array($markers) : $markers).";\n";
    if($center = $options['center']) $onload .= "map_options.center = ".(is_array($center) ? json_encode($center) : json_encode(explode(',', $center))).";\n";
    if($zoom = $options['zoom']) $onload .= "map_options.zoom = $zoom\n";
    $onload .= "gmap3(map_options);\n";
    $__header['onload'] .= $onload;      
  }
  return "
    <div id='$id' class='$class' $style></div>
  ";
}

  //if(!$options['site_id']) $options['site_id'] = $_SESSION['site_id'];
  //$map_options = $options ? json_encode($options) : '{}';
  //if($init) $__header['onload'] .= "debug('gmap3: doc ready id=' + id + ' len =' + len);gmap3('$id', markers, ".$map_options.");\n";

function gmap3_markers($options=NULL) {
  $locs = $options['markers'] ?: array();
  if(is_object($locs)) $locs = array($locs);
  $markers = $locs;
  
  $output = "
  markers = ".json_encode($markers).";\n"; 
  return $output;
}
*/
 
// takes an array of properties or locations, returns javascript representation of data
// used by googlemap to generate markers
// todo: load with ajax ? 

// google maps using Instamapper to show current location of device
// device ID: 17407152679632113300
function googlemap_tracker($device_id, $width=400, $height=300, $zoom=13, $type='roadmap', $units='metric') {
  return '
<!-- BEGIN INSTAMAPPER CODE -->
Live GPS tracking: <a href="http://www.instamapper.com/ext?key='.$device_id.'" target="_blank">InstaMapper.com</a>
<br><br>
<iframe style="border:1px solid;" width="600" height="335" frameborder="0" scrolling="no" src="http://www.instamapper.com/ext?key='.$device_id.'&width=400&height=300&zoom=13&type=roadmap&units=metric&coords=d">
</iframe>
';
}

function google_get_app($name_or_id) {
  if(isint($name_or_id)) return get_object('google_application', $name_or_id);
  return find_object('google_application', array('name' => $name_or_id));
}


// new API functions
// checks if a given google id has authenticated the app for offline use
function google_authenticate_app($google_id, $application, $options=NULL) {
  $debug = false;
  
  require_once 'google/google-api-php-client/src/apiClient.php';

  $appObj = google_get_app($application); 
  //dump($appObj);
  if(!$appObj) die("google_authenticate_app: Could not find application $application");
  
  $app_name      = $appObj->name;  
  $client_id     = $appObj->client_id; 
  $client_secret = $appObj->client_secret;
  $redirect_uri  = 'http://'.$_SERVER['HTTP_HOST'].$appObj->redirect_uri; // todo: allow https 
  $api_key       = $appObj->api_key;
  $scope_str     = $appObj->scope;
  $scope         = explode(' ', $scope_str); 

  $client = new apiClient();
  $client->setApplicationName($app_name);  
  $client->setClientId($client_id);
  $client->setClientSecret($client_secret);
  $client->setRedirectUri($redirect_uri);
  $client->setDeveloperKey($api_key);
  $client->setScopes($scope);
  $client->setAccessType('offline');
  $client->setApprovalPrompt('auto');
  $client->setUseObjects(true);

  //$search = array('service' => 'google', 'account_id' => $google_id, 'scope' => $scope_str);
  $search = array('service' => 'google', 'account_id' => $google_id);
  
  //$at = $_SESSION['google_access_token'][$app_name][$google_id];
  //if($at) {
  //  $client->setAccessToken($at);
  //  if($debug) echo("We are already authenticated<br>");
  //  if($debug) dump($_SESSION['access_token']);
  //} else 
  
  if($tokenObj = find_object('access_token', $search)) { // update
    // echo("Authenticating...<br>");
    if($refresh_token = $tokenObj->token) {
      // echo("token=$refresh_token<br>");
      $client->refreshToken($refresh_token);
      if($access_token = $client->getAccessToken()) {
        $token = json_decode($access_token);
        if($debug) dump($token);
        $_SESSION['google_access_token'][$app_name][$google_id] = $at = $access_token;
        //echo("at2=".$_SESSION['google_access_token']."<br>");
      } else {
        if($debug) echo("Failed to authenticate $google_id offline for $app_name<br>");
        return NULL;
      }
    } else {
      if($debug) echo("No refresh token found<br>");
      return NULL;
    }
  } else {
    if($debug) {
      echo("No refresh token object found<br>");
      dump($search);
    }
    return NULL;
  }
  return $client;
}

/* takes a client object (must be authorized), a google account name an an event array, inserts into google calendar
  event['summary']    : string
  event['location']   : string
  event['visibility']   : string default/public/private
  event['start']      : mysql datetime  
  event['end']        : mysql datetime        
  event['attendees']  : array of emails, or array of objects: 
   attendee->email
   attendee->displayName
   
*/

function google_tag_manager($id) {
  return "
  <!-- Google Tag Manager -->
  <noscript><iframe src=\"//www.googletagmanager.com/ns.html?id={$id}\"
  height=\"0\" width=\"0\" style=\"display:none;visibility:hidden\"></iframe></noscript>
  <script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
  new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
  j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
  '//www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
  })(window,document,'script','dataLayer','GTM-PK4BC4');</script>
  <!-- End Google Tag Manager -->
  ";
}

function google_add_calendar_event($client, $account_name, $eventAr, $options=NULL) {
  require_once 'google/google-api-php-client/src/apiClient.php';
  require_once 'google/google-api-php-client/src/contrib/apiCalendarService.php';

  $access_token = $client->getAccessToken();
  if(!$access_token) die("google_add_calendar_event: client not authorized"); // todo: authenticate
  $timeZone = $eventAr['timeZone'] ?: date_default_timezone_get();
  
  $service = new apiCalendarService($client);
  $event = new Event();
  
  if($summary = $eventAr['summary']) $event->setSummary($summary);
  if($location = $eventAr['location']) $event->setLocation($location);
  if($visibility = $eventAr['visibility']) $event->setVisibility($visibility);
  if($transparency = $eventAr['transparency']) $event->setTransparency($transparency);
    
  $start_time = $eventAr['start'];
  $start = new EventDateTime();
  if($timeZone) {
    $start->setTimeZone($timeZone);
    $datetime = gmdate('Y-m-d\TH:i:s', strtotime($start_time));
  } else {
    $datetime = sql2atom($start_time);
  }
  $start->setDateTime($datetime);
  $event->setStart($start);

  //dump($start);

  $end_time = $eventAr['end'];
  $end = new EventDateTime();
  if($timeZone) {
    $end->setTimeZone($timeZone);
    $datetime = gmdate('Y-m-d\TH:i:s', strtotime($end_time)); // no offset needed
  } else {
    $datetime = sql2atom($end_time); // with offset
  }
  $end->setDateTime($datetime);
  $event->setEnd($end);

  $attendees = $eventAr['attendees']; 
  $event_attendees = array();
  if(is_array($attendees)) {
    foreach($attendees as $att) {
      $attendee = new EventAttendee();
      if(is_object($att)) {
        $attendee->setEmail($att->email);
        $attendee->setDisplayName($att->displayName);
        //$attendee->setEmail($att);
      } else {
        $attendee->setEmail($att);
      }
      $event_attendees[] = $attendee;
    }
    //if(isAssoc($attendees)) {
    //  foreach($attendees as $email => $name) {
    //    $attendee = new EventAttendee();
    //    $attendee->setEmail($email);
    //    $attendee->setDisplayName($name);
    //    $event_attendees[] = $attendee;
    //  }
    //} else {
    //}    
    $event->attendees = $event_attendees;
  }

  $createdEvent = $service->events->insert($account_name, $event);
  
  //echo ("created event ".$createdEvent->getId().html_break());
    
  //$events = $service->events->listEvents($google_account_name);

  return $createdEvent;
}

/** Google Analytics e-commerce Javascript snippets */

// Function to return the JavaScript representation of a TransactionData object.
function getTransactionJs(&$trans) {
  return <<<HTML
ga('ecommerce:addTransaction', {
  'id': '{$trans['id']}',
  'affiliation': '{$trans['affiliation']}',
  'revenue': '{$trans['revenue']}',
  'shipping': '{$trans['shipping']}',
  'tax': '{$trans['tax']}'
});
HTML;
}

// Function to return the JavaScript representation of an ItemData object.
function getItemJs(&$transId, &$item) {
  return <<<HTML
ga('ecommerce:addItem', {
  'id': '$transId',
  'name': '{$item['name']}',
  'sku': '{$item['sku']}',
  'category': '{$item['category']}',
  'price': '{$item['price']}',
  'quantity': '{$item['quantity']}'
});
HTML;
}

/** 
<!-- Begin HTML -->
<script>
ga('require', 'ecommerce');

<?php
echo getTransactionJs($trans);

foreach ($items as &$item) {
  echo getItemJs($trans['id'], $item);
}
?>

ga('ecommerce:send');
</script>
*/
