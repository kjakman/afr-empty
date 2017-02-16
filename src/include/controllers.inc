<?php

function controller_test($siteObj, $pageObj, $options = array()) {
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $scope->foo = 'bar';
  return $scope;
}

function controller_login($siteObj, $pageObj, $options = array()) {
  global $u_id;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $ref = $_GET['ref'];
  if($u_id && $ref) {
    $scope->redirect = $ref;
  }
  return $scope;
}

function controller_register($siteObj, $pageObj, $options = array()) {
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $scope->register = "bar";
  return $scope;
}

function controller_generic($siteObj, $pageObj, $options = array()) {
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  return $scope;
}

function controller_calendar($siteObj, $pageObj, $options = array()) {
  global $__header, $u_id, $__CLIENT_ID, $__USER;
  $ver = $_SESSION['version'];
  $scope->hide_menu = 1;
  
  $__header['end_scripts'][] = "/afr/js/admincal.js?v=$ver";
  $__header['end_scripts'][] = "/afr/js/admincal-dialog.js?v=$ver";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.js";
  /** todo: support other languages, use $_SESSION['locale']  */
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/locale/bootstrap-table-en-US.js";    
  $__header['css'][] = "/afr/css/afr.css";
  $__header['css'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.css";
  $__header['css'][] = "/afr/css/admincal.css?v=$ver";
  $__header['css'][] = "/afr/css/afr_gmenu.css";
      
  $cp = $options['cal_params'] ?: new stdClass;
  
  $ptype = $siteObj->property_type ?: 'shortstay';
  $host_ids = user_host_list($u_id);  
  $psearch = array('host_id' => $host_ids);

  
  $scope->show_inactive = $show_inactive = isset($_GET['si']) ? $_GET['si'] : 1;
  if(!$show_inactive) $psearch['active'] = 1;
          
  //$scope->rentals = find_objects($ptype, $psearch);
  $rentals = find_objects($ptype, $psearch, ['fields' => ['id', 'name']]);
  array_unshift($rentals, ['id' => 0, 'name' => "?"]);
  $scope->rentals = $rentals;
  $scope->sites = find_objects('site', ['client_id' => $__CLIENT_ID, 'property_type' => $ptype, 'active' => 1], ['fields' => ['site.id', 'site.name', 'site.shortname']]);
  $scope->legal_entities = find_objects('legal_entity', ['client_id' => $__CLIENT_ID, 'active' => 1], ['fields' => ['legal_entity.id', 'legal_entity.name', 'legal_entity.shortname']]);
  $scope->agents = find_objects('agent', ['client_id' => $__CLIENT_ID, 'active' => 1], ['fields' => ['agent.id', 'agent.name'], 'sort' => 'agent.name']);
  $scope->clients = find_objects('org', ['client_id' => $__CLIENT_ID, 'active' => 1], ['fields' => ['org.id', 'org.org_name'], 'sort' => 'org.org_name']);
  $scope->host_ids = $host_ids;
                     
  $start = date('Y-m-01');
  $scope->data = ['start' => $_GET['start'] ?: $start, 'mode' => 'calendar', 'period' => $_GET['p'] ?: 1, 
                  'rentals' => $rentals, 'view' => 'month', 'host_ids' => $host_ids, 
                  'user_level' => $__USER->user_level, 'user_id' => $__USER->id]; /** new cal params */
  //echo("si={$show_inactive}");
  //dump($host_ids);
  //dump($psearch);
  //dump($rentals);
  return $scope;                                              
 }

function controller_search($siteObj, $pageObj, $options = array()) {
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $results = array();
  if($term = $_GET['s']) {
        
    // page content
    if($result = search_result($siteObj, 'page_content', $term, array('title', 'content'), 'id', $options))
      $results = array_merge($results, $result);

    // articles / blogs
    if($result = search_result($siteObj, 'article', $term, array('title', 'content'), 'id', $options))
      $results = array_merge($results, $result);

    // comments
    if($result = search_result($siteObj, 'comment', $term, array('title', 'content'), 'id', $options))
      $results = array_merge($results, $result);

    // events
    if($result = search_result($siteObj, 'event', $term, array('name', 'notes'), 'id', $options))
      $results = array_merge($results, $result);
    
  }
  $scope->results = $results;
  //dump($scope->result);
  return $scope;
}

function controller_site_edit($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $ver = $_SESSION['version'] ?: date('md');

  $__header['scripts'][] = "/afr/js/afr_cms_jstree.js?v=$ver";
  $__header['css'][] = "/afr/bower/jstree/dist/themes/default/style.min.css";
  $__header['end_scripts'][] = "/afr/bower/jstree/dist/jstree.min.js";
    
  return $scope;
}

/** generic controller for back-end, e.g site_edit. Called from app_data: cms-explore */
function controller_cms_explore($siteObj, $pageObj, $options = array()) {
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $language = pick_first($scope->language, $_SESSION['language'], $siteObj->default_language);
  $obj_type = $scope->obj_type;
  $obj_id = $scope->obj_id;
  $obj = $obj_type && $obj_id ? get_object($obj_type, $obj_id) : new stdClass;
  switch($obj_type) {
    case 'site_page': // add page_content for chosen language
      if($obj_id) {
        $obj = site_find_content($siteObj, $obj_id, $language); 
      } else { /** add page */
        $obj->id = $obj->obj_id = 0;
        $obj->name = $name = $scope->name;
        $obj->active = 1;
        $obj->show_menu = 1;
        $obj->parent_id = $parent_id = $scope->parent_id;
        $obj->user_level = 0;
        $safe_name = url_safe($name);
        $parent_path = $parent_id ? find_object('page_content', ['page_id' => $parent_id, 'language' => $language], 'path') : '';
        $obj->path = str_replace("//", "/", clean_path("{$parent_path}/{$safe_name}/"));
      }
      $obj->foo = 'bar';
      break;
    case 'site': // add site_content for chosen language
      break;
    default:
      break;
  }
  $scope->obj = $obj;
  return $scope;
}


/** uses rental_search, object type is location */
function controller_location($siteObj, $pageObj, $options = array()) {
  return controller_geo_location($siteObj, $pageObj, $options);
}

/** uses rental_search, object type is geo_city */
function controller_geo_location($siteObj, $pageObj, $options = array()) {
  global $__header, $u_id, $__LANG;
  $min_radius = 2250;
  
  $scope = new stdClass;
  $scope->property_type = $ptype = pick_first($siteObj->property_type, $_SESSION['property_type'], 'shortstay');
  
  /** preprocessing - find bounds */
  //$__header['scripts'][] = "/afr/bower/jquery-ui-map/ui/min/jquery.ui.map.full.min.js";
  //$__header['scripts'][] = "/afr/js/afr_gmap.js?v=$ver";
  $__header['css'][] = "/afr/css/afr-air.css";

  $slug = $_SESSION['slug'];
  $obj = $locObj = $_SESSION['this_object'];
  $obj_type = $scope->obj_type = $_SESSION['this_object_type'];
  $obj_id = $scope->obj_id = $_SESSION['this_object_id'];
  
  $scope->slug = $slug;
  $scope->obj = $obj;
  
  
  if($obj) {
    $center = loc2center($obj);
    $obj_center = json_encode($center);
    $obj_radius = $obj->location_radius;
    $bounds = any2bounds($obj->location_bounds, true) ?: [];  
    if($center && !$bounds) {
      if($obj->population > 0) {
        $radius = min(round($locObj->population / 10), 10000); // bigger radius for big cities, max 10km
      } else {
        $radius = DEFAULT_RADIUS;
      }
      $radius = max($radius, $min_radius); // bigger radius for big cities, min 3km
      
      $bounds = radius2bounds($obj, $radius, true);      
      print_log("calculated bounds {$bounds} radius={$radius}", 'property-search', LOG_LEVEL_TEST);
      
    }
    
    
    print_log("location set: slug={$slug} type={$obj_type} id={$obj_id} obj-center {$obj_center} radius={$obj_radius} obj-bounds={$obj->location_bounds} ", 'property-search', LOG_LEVEL_TEST);
    
    $parent_type = $pageObj->page_type == PAGE_LOCATION ? 'location': 'geo_city';
    
    // get location description    
    $search = ['parent_type' => $parent_type, 'parent_id' => $obj->id, 'language' => $__LANG];
    if($descObj = find_object('object_description', $search)) {
      $scope->location->title = $descObj->title;
      $scope->location->description = $descObj->description;
      $scope->location->description_id = $descObj->id;
    } elseif($descObj = find_object('object_description', ['parent_type' => $parent_type, 'parent_id' => $obj->id])) {
      $descData = ['language' => $__LANG];
      foreach(['site_id', 'parent_type', 'parent_id', 'type', 'description'] as $f) $descData[$f] = $descObj->$f;
      list($desc_id, $errors) = add_object('object_description', $descData);
      if($desc_id) {
        $scope->location->title = $descObj->title;
        $scope->location->description = $descObj->description;
        $scope->location->description_id = $desc_id;
      }
      if($errors) $scope->error = $errors;
    }
    
  } elseif($slug) {
    list($status, $acc, $lat, $lng, $bounds) = google_geocode($slug);
    print_log("geocoding: slug={$slug} status={$status} lat={$lat} lng={$lng}", 'property-search', LOG_LEVEL_TEST);
    
    if($status==200) {
      $scope->http_code = "200"; //override error set in set_env.inc due to unknown slug
      $center = [$lat, $lng];
      $locObj = center2loc($center);
      $boundsObj = $bounds ? json_decode($bounds) : radius2bounds($locObj, DEFAULT_RADIUS);
      $bounds = any2bounds($boundsObj, true);
    }
  } else {
    $scope->error = "Neither location object nor slug";
    $scope->template = "404"; 
    return $scope;
  }
  
  if($bounds) {
    $center = bounds2center($bounds);
    $loc = center2loc($center);
    $radius = bounds2radius($bounds);
    
    if($obj_radius > $min_radius) {
      print_log("Loc radius > min ($min_radius): $locObj->location_radius", 'property-search', LOG_LEVEL_TEST);
      $min_radius = $locObj->location_radius;
    }
      
    print_log("\n\nradius=$radius", 'property-search', LOG_LEVEL_TEST);
    if($radius < $min_radius) {
      //print_log("zooming out".dump($bounds,true), 'property-search', LOG_LEVEL_TEST);
      $bounds = radius2bounds($loc, $min_radius, true);
      $radius = bounds2radius($bounds);
      //print_log("new radius=$radius".dump($bounds,true), 'property-search', LOG_LEVEL_TEST);
      
    }
    
    $center_str = $scope->center = json_encode($center);
    $bounds_str = $scope->bounds = json_encode($bounds);
  } else {
    $scope->error = "Could not find location slug={$slug} name={$locObj->name}";
    $scope->template = "404"; 
    return $scope;    
  }
  
  print_log("OK: Found bounds: center={$center_str} bounds={$bounds_str} radius={$radius}", 'property-search', LOG_LEVEL_TEST);

  $options['bounds'] = $bounds_str;
  $search_scope = controller_rental_search($siteObj, $pageObj, $options);
  
  $scope = object_merge($scope, $search_scope);
  return $scope;
}
  
function controller_rental_search($siteObj, $pageObj, $options = array()) {   
  global $__header, $u_id, $__DEFAULT_BOUNDS;

  $ver = $_SESSION['version'] ?: date('md');
  $__header['css'][] = "/afr/css/afr-air.css";

  $scope = $options['scope'] ?: new stdClass;  // ? array2obj($options['scope']) : new stdClass;
  $scope->property_type = $ptype = pick_first($siteObj->property_type, $_SESSION['property_type'], 'shortstay');
  $scope->amenities = rental_amenities($siteObj, null, array('searchable' => 1));

  /** todo: */
  $scope->property_link = site_page_link($siteObj, PAGE_SHORTSTAY);
  
  if($rentals = $scope->rentals) { /** new - search now happens in app_data rental-search, returns json */
    $scope->loaded = 1;
    $preset = 1;
  } else {
    $scope->loaded = 1;
    $preset = 0;
    $search = $_GET;
    
    if($bounds = $options['bounds']) {
      $search['bounds'] = $bounds; // from controller_geo_location or controller_location
    } elseif($bounds = $search['bounds']) {
      //print_log("rental_search: expl. bounds:".dump($bounds,true), 'property-search', LOG_LEVEL_TEST);            
    } elseif($loc = $search['loc']) {
      $loc = urldecode($loc);
      list($status, $acc, $lat, $lng, $bounds) = google_geocode($loc);
      if($status==200) {
        $scope->http_code = "200"; //override error set in set_env.inc due to unknown slug
        $center = [$lat, $lng];
        $locObj = center2loc($center);
        $boundsObj = $bounds ? json_decode($bounds) : radius2bounds($locObj, DEFAULT_RADIUS);
        $bounds = any2bounds($boundsObj, true);        
        $search['bounds'] = json_encode($bounds);
      }
    }
    
    if(!$search['bounds']) $search['bounds'] = $siteObj->default_bounds ?: $__DEFAULT_BOUNDS;
    
    /** widen search by 100%, as map will show bounds + a little extra... */
    if(1) {
      $search_bounds_json = $search['bounds'];
      $search_bounds = json_decode($search['bounds']);
      $search_radius = bounds2radius($search_bounds);
  
      $search_center = bounds2center($search_bounds);
      $search_loc = center2loc($search_center);
      
      $factor = 2;
      $wide_radius = $search_radius * $factor;
      $wide_bounds = radius2bounds($search_loc, $wide_radius, true);
    
      $search['bounds'] = $wide_bounds_json = json_encode($wide_bounds);
      
      //print_log("Widened search from radius = $search_radius to $wide_radius", 'property-search', LOG_LEVEL_TEST);
      //print_log("Was: $search_bounds_json", 'property-search', LOG_LEVEL_TEST);
      //print_log("Now: $wide_bounds_json", 'property-search', LOG_LEVEL_TEST);
    }
    
    $result = rental_search($search);
    if($error = $result->error) $scope->error = $result->error;  
    
    $data = $result->data ?: [];
    foreach($data as $k=>$v) $scope->$k = $v;
    $rentals = $data->rentals;
    
    $scope->bounds = $search_bounds; /** reset to original */
  }

  $count = count($rentals);  
  if(count($rentals)) {
    $scope->filters = $filters = rental_search_filters($search);
  } else {
    $scope->tips = $tips = rental_search_tips($search);
  }
  
  
  $center_str = $scope->center = json_encode($scope->center);
  $bounds_str = $scope->bounds = json_encode($scope->bounds);
  
  print_log("controller_rental_search v2: count=".count($rentals)." preset={$preset} center={$center} bounds={$bounds}", 'property-search', LOG_LEVEL_TEST);
  
  return $scope;
}


function controller_rental_feedback($siteObj, $pageObj, $options = array()) {
  $obj = $_SESSION['this_object'];
  $obj_type = $scope->obj_type = $_SESSION['this_object_type'];
  $obj_id = $scope->obj_id = $_SESSION['this_object_id'];

  $scope->feedback = $obj;
  return $scope;  
}

function controller_sitemap($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $tree = site_sitemap($siteObj, []);
  //$search = ['address_country' => 'PT']; // for testing
  if($ptype = $siteObj->property_type) {    
    $ptree = site_sitemap_property_tree($siteObj, ['type' => $ptype, 'search' => $search]);
    $tree = array_merge($tree, $ptree);
  }
  if($siteObj->golf_site) {
    $gtree = site_sitemap_golf_tree($siteObj, ['search' => $search]);
    $tree = array_merge($tree, $gtree);
  }
  $scope->sitemap_xml = $xml = site_sitemap_xml($siteObj, ["tree" => $tree]);
  //echo(form_text('foo', $xml));die();
  $xmlfile = docroot().'sitemap.xml';
  $len = write_file($xmlfile, $xml);
  
  $scope->sitemap = $tree;
  return $scope;  
};

function controller_event_calendar($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header, $u_level,$__USER_LEVELS;
  $ver = $_SESSION['version'] ?: date('md');
  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $__header['end_scripts'][] = "/afr/bower/fullcalendar/dist/fullcalendar.js";
  $__header['end_scripts'][] = "/afr/bower/ubilabs-geocomplete/jquery.geocomplete.min.js";
  $__header['css'][] = "/afr/bower/fullcalendar/dist/fullcalendar.css";

  $__header['end_scripts'][] = "/afr/js/afr_gmap.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-confirmation2/bootstrap-confirmation.js";    
  $__header['end_scripts'][] = "/afr/js/event-form.js?v={$ver}";    

  $__header['css'][] = "/afr/jquery/periodpicker/build/jquery.periodpicker.min.css";
  $__header['end_scripts'][] = "/afr/jquery/periodpicker/build/jquery.periodpicker.full.min.js";
  
  $calOptions = array();
  $site_id = $scope->site_id = $siteObj->id;
  
  $scope->calendar_edit = $auth_edit = $u_level >= USER_LEVEL_EDITOR;
  $site_id = $siteObj->id;
  $scope->calendar_url = $url = ajax_operation_link('agenda-calendar-events', array('site_id' => $site_id, 'edit' => $auth_edit), array('public' => true));
  $calOptions = array("selectable" => true, "editable" => $auth_edit, "url" => $url, "site_id" => $site_id, "timeFormat" => "H:mm");
    
  if($in) $calOptions['defaultDate'] = $in;
  $scope->calendar_options = $calOptions;
  $scope->user_levels = $__USER_LEVELS;
  return $scope;
}


/** add rental */
function controller_rental_add($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $ver = $_SESSION['version'];  
  //$__header['end_scripts'][] = "/afr/js/afr_gmap.js";
  $__header['end_scripts'][] = "/afr/bower/ubilabs-geocomplete/jquery.geocomplete.min.js";
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $scope->currency = "EUR";
  $scope->host_ids = $host_ids = user_host_list($u_id) ?: array();
  
  $scope->rental_types = find_objects("hosting_property_type", array('active' => 1));
  $scope->room_types = find_objects("hosting_room_type", array('active' => 1));
    
  return $scope;  
}

/** host rental list */
function controller_rental_list($siteObj, $pageObj, $options) {
  global $__USER, $u_id;

  /** rental list page - and rental list tab (for single rental edit */    
  $ptype = $scope->property_type = $siteObj->property_type ?: 'shortstay';
  
  $host_ids = user_host_list($u_id);
  $pSearch = array("host_id" => $host_ids);
  $pSearch = array_merge_json($pSearch, $siteObj->property_filters);
  $start = $scope->start = $_GET['start'] ?: 0;        
  $pOptions = array('limit' => 10, 'start' => $start);
  
  $scope->rental_list = $rentals = find_objects($ptype, $pSearch, $pOptions);
  $scope->rental_count = $count = count($rentals);
  
  foreach($rentals as $aptObj) { /** check if we can list */
    if($aptObj->active) continue;
    $steps = property_remaining_steps($siteObj, $aptObj->type, $aptObj->id);
    $aptObj->steps_remaining = count($steps); 
  }

  /** only on rental list page */    
  $descObjs = find_objects('description_type', array('generic' => 1), array("sort" => "id desc"));
  $generic_types = [];
  foreach($descObjs as $descObj) {
    $key = "text_".url_safe($descObj->name)."-example";
    $descObj->example = phrase($key);
    $generic_types[] = $descObj->id;
  }
    
  $scope->description_types_generic = $descObjs;

  $host_id = 0;
  if($__USER->user_level == USER_LEVEL_HOST) {
    $host_id = $u_id;
  } else {
    $host_ids = user_host_list($u_id);
    if(count($host_ids) > 1) {
      $rental_host_ids = find_objects($ptype, ['host_id' => $host_ids], ['fields' => 'distinct host_id']);
      if(count($rental_host_ids) == 1) {
        $host_id = $rental_host_ids[0];
      } else {
        $scope->error = "You are managing rentals for multiple hosts. Generic descriptions for multiple hosts is not yet implemented. Please contact support";
      }
    }
  }
      
  if($host_id) {
    // look for existing common/generic descriptions
    $descObjs = find_objects('property_description', ["host_id" => $host_id, "property_type" => $property_type, "property_id" => 0, "type" => $generic_types, "active" => 1]);
    $descriptions = [];
    foreach($descObjs as $descObj) {
      $type = $descObj->type;
      $descTypeObj = get_object('description_type', $type);
      if(!$descTypeObj->private) $description_more .= html_h4(phrase($descTypeObj->name, CAPITALIZE)).nl2br($descObj->description);        
      $descriptions[$descObj->type] = $descObj;
    }
  }
  $scope->host_id = $host_id;
  $scope->guides_generic = $descriptions;
  
  $scope->template = 'rental-list.html'; 

  return $scope;
  
}

/** edit rental */
function controller_rental_edit($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $ver = $_SESSION['version'];

  if(!$u_id) {
    $scope->redirect = page_link(PAGE_LOGIN)."?ref=".urlencode(this_path());
    $scope->template = "403";
    return $scope;
  }
  
  $id = $obj_id = $apt_id = $scope->obj_id = $scope->apt_id = pick_first($scope->rental_id, $scope->apt_id, $scope->obj_id, $_GET['apt_id'] ?: $_GET['obj_id'], $options['apt_id'] ?: $options['obj_id'], $_SESSION['this_object_id']);
  $t = $ptype = $scope->property_type = $siteObj->property_type ?: 'shortstay';
  
  /** host rental list use same URL - /edit-rental/ */
  if(!$id) return  controller_rental_list($siteObj, $pageObj, $options);

  /** OK: edit single rental */  
  $__header['end_scripts'][] = "/afr/bower/ubilabs-geocomplete/jquery.geocomplete.min.js";
  //$__header['end_scripts'][] = "/afr/js/admincal.js?v=$ver";
  
  $__header['end_scripts'][] = "/afr/js/admincal-dialog.js?v=$ver";
  //$__header['css'][] = "/afr/css/admincal.css?v=$ver";

  $__header['css'][] = "/afr/css/afr_tooltip.css";
  $__header['css'][] = "/afr/css/afr_form.css";
  $__header['scripts'][] = "/afr/bower/jquery-validate/dist/jquery.validate.min.js";
  $__header['scripts'][] = "/afr/js/custom_validators.js";
  if($_SESSION['lang'] != 'en') $__header['scripts'][] = "/afr/bower/jquery-validate/localization/messages_".$_SESSION['lang'].'.js';
    
  jfu_dependencies();
  
  $aptObj = get_object($t, $id);
  print_log("controller_rental_edit t=$t id=$id apt=".dump($aptObj,true), 'app', LOG_LEVEL_TEST);
  
  $scope->auth_edit = $auth_edit = auth_rental($aptObj);
  if(!auth_rental($aptObj)) return controller_error("Edit Rental \"{$aptObj->name}\" not authorized");
  $scope = controller_rental_detail($siteObj, $pageObj, $options);

  /** moved from rental_detail */
  $steps_remaining = 0;
  if($source_id = $aptObj->source_id) {
    $scope->import_url = ajax_operation_link('rental-import', array('site_id' => $siteObj->id, 'property_type' => $aptObj->type, 'apt_id' => $id, 'source_id' => $source_id), array('public' => false));
  } else {
    $scope->steps_remaining = property_remaining_steps($siteObj, $aptObj->type, $aptObj->id);
    //if(count($steps_remaining) && $aptObj->active) update_object('property', array('active' => 0), $aptObj->id); // deactivate;
  }
  
  $scope->uploader = property_uploader($ptype, $id, array("view" => "grid", "handler" => "property_photo_handler")); // doesn't work in switch, as dependencies are not loaded
  
  
  $scope->view = $template = pick_first($_GET['view'], $_GET['template'], $options['template'], "_rental-edit-location.html");
  if($template && strpos($template, '_rental-edit-') === false) $template = $scope->view = "_rental-edit-{$template}.html"; // allow shortform
  
  if($template && strpos($template, '_rental-edit-') === false) $template = $scope->view = "_rental-edit-{$template}.html"; // allow shortform
  switch($template) { // from app_data/fetch-template
    case "_rental-edit-photos.html":
      $mediaData = array("user_id" => $u_id, "site_id" => $siteObj->id, "parent_type" => $ptype, "parent_id" => $id, "parent_field" => "media");
      if($aptObj->source_id == SOURCE_ID_INTERHOME) { /** todo: check if media is list of external IDs */
        $mediaData['inline'] = 1;
      }
      $scope->media_data = $mediaData; 
      break;
    case "_rental-edit-calendar.html":
      $scope->single_calendar_edit = true;
      //$scope->single_calendar_url = "/afr/XML/HV/property-calendar.php?format=event&id=$id&edit=1";
      $scope->single_calendar_url = ajax_operation_link('rental-calendar-events', array('id' => $id, 'edit' => 1));        
      $scope->single_calendar_options = array("selectable" => true, "editable" => true, "weekNumbers" => true); 
        // "events" => "/afr/XML/HV/property-calendar.php?format=event&id=$id&edit=1");
      break;
    case "_rental-edit-description.html":
      $scope->short_desc_example = $phrase = phrase("text_short-description-example");
      //dump($phrase);
      break;
    case "_rental-edit-guide.html":
      $desc_types = array(DESC_TYPE_PROPERTY,DESC_TYPE_AREA);
      if($siteObj->golf_site) $desc_types[] = DESC_TYPE_GOLF;
      $desc_types[] = DESC_TYPE_FOOD; // private 
      $desc_types[] = DESC_TYPE_RULES;
      $desc_types[] = DESC_TYPE_INTERACTION;
      $desc_types[] = DESC_TYPE_DIRECTIONS; // private
      $desc_types[] = DESC_TYPE_CHECKIN; // private 
      //dump($desc_types);
      $descObjs = find_objects('description_type', array('id' => $desc_types), array("sort" => "private, id desc"));
      foreach($descObjs as &$descObj) {
        $key = "text_".url_safe($descObj->name)."-example";
        $descObj->example = phrase($key);
      }
      $scope->description_types = $descObjs;
      // not in use DESC_TYPE_TRAVEL,DESC_TYPE_QUICK,DESC_TYPE_ALBUM,DESC_TYPE_STRAP,

      break;
    case "_rental-edit-amenities.html":
      $scope->amenities = rental_amenities($siteObj, $aptObj, array('searchable' => 0));
      //$scope->debug = dump($scope->amenities,true);
      //dump($facArray);
      break;
    case "_rental-edit-import.html":
      $scope->sources = find_objects('calendar_import', array('property_type' => $ptype, 'apt_id' => $id, 'active' => 1));
      break;
      
    case "_rental-reviews.html":
      $start = $scope->start = $_GET['start'] ?: 0;
      $limit = $scope->limit = 10;
      $searchOptions = array("start" => $start, "limit" => $limit);        
      $search = array("host_id" => $host_id, "apt_id" => $id, "published" => 1, "site_id" => $siteObj->id);

      $scope->reviews = find_objects("feedback", $search, $searchOptions);
      $scope->review_count = count_objects("feedback", $search);
      
      break;
    case "_rental-edit-list.html":
      
      $host_ids = user_host_list($u_id);
      $pSearch = array("host_id" => $host_ids);
      $pSearch = array_merge_json($pSearch, $siteObj->property_filters);
      $start = $scope->start = $_GET['start'] ?: 0;        
      $pOptions = array('limit' => 10, 'start' => $start);
      
      $scope->rental_list = $rentals = find_objects($ptype, $pSearch, $pOptions);
      $scope->rental_count = $count = count($rentals);
      
      foreach($rentals as $aptObj) { /** check if we can list */
        if($aptObj->active) continue;
        $steps = property_remaining_steps($siteObj, $aptObj->type, $aptObj->id);
        $aptObj->steps_remaining = count($steps); 
      }
      break;
      
    default:
      break;
  }
  

  return $scope;
  
}
  
/** alias */
function controller_rental($siteObj, $pageObj, $options = array()) {
  return controller_rental_detail($siteObj, $pageObj, $options);
}

function controller_rental_detail($siteObj, $pageObj, $options = array()) {
  global $u_id, $__USER, $__header, $__LANGUAGE;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $scope->stack = caller_stack();
      
  extract($_GET);
  
  //$__header['end_scripts'][] = "/afr/bower/fullcalendar/dist/fullcalendar.min.js";
  $__header['end_scripts'][] = "/afr/bower/fullcalendar/dist/fullcalendar.js";
  $__header['css'][] = "/afr/bower/fullcalendar/dist/fullcalendar.css";
  $__header['css'][] = "/afr/bower/foundation-icon-fonts/foundation-icons.css";
  $__header['css'][] = "/afr/css/afr-air.css";

  $ver = $_SESSION['version'] ?: date('md');
  
  $global = $_SESSION['global_scope'];
  $loc_types = $global->location_types;
  $locArray = $loc_types ? explode(',', $loc_types) : array();
  
  $imageAr = array();
  if($data = $options['data']) { // from fetch-template
    extract($data);    
  }
  
  $t = $ptype = $scope->property_type = $siteObj->property_type ?: 'shortstay';
  $id = $obj_id = $apt_id = $scope->obj_id = $scope->apt_id = pick_first($scope->rental_id, $scope->apt_id, $scope->obj_id, $_GET['apt_id'] ?: $_GET['obj_id'], $options['apt_id'] ?: $options['obj_id'], $_SESSION['this_object_id']);  
  if(!$id) return controller_error("Missing rental ID");

  $aptObj = get_object($t, $id);
  if(!$aptObj) return controller_error("Rental not found");
      
  /** This controller is also used by rental edit */
  $edit = $pageObj->page_type == PAGE_EDIT_PROPERTY;
  $scope->auth_edit = $auth_edit = auth_rental($aptObj);  
  if($edit && !$auth_edit) return controller_error("None of your rentals found");
  
  /** viewing deactivated property */ 
  if(!$aptObj->active && !$edit) {
    if($auth_edit) {
      $scope->message = "Preview: Rental not activated";
    } else {
      return controller_error("No active rental found", '403');
    }
  }
  
  /** viewing active property - not edit - update page views */ 
  if($aptObj->active && !$edit) {
    $pv = ($aptObj->pageviews ?: 0) + 1;
    update_object('property', ['pageviews' => $pv], $aptObj->id);
  }
  
  $qs = get_query_string();
  $scope->search_url = $_SESSION['search_url'] = parent_path().($qs ? "?{$qs}" : "");
  
  $in = $_GET['in'] ? date2sql($in) : '';
  $out = $_GET['out'] ? date2sql($out) : '';
  $ng = $_GET['ng'] ?: 1; 
  $nd = $in && $out && $in > $out ? datediff('days', $in, $out) : 0;

  $url = property_geolink($aptObj);
  $this_url = this_path();
  $script = $_SERVER['SCRIPT_NAME'];
  $method = $_SERVER['REQUEST_METHOD'];
  $ref    = $_SERVER['HTTP_REFERER'];
  
  $redirect = $url != $this_url && !$edit && !$scope->ajax && $method == 'GET' && !strpos($script, 'app_data.php') ? 1 : 0;
  if(0 && $redirect) {
    print_log("rental_controller: redirecting: script: {$script} method:{$method} ref:{$ref}", 'rental', LOG_LEVEL_TEST);
    $qs = get_query_string();
    if($qs) $url .= "?{$qs}";
    redirect($url);
  }
  
  $scope->id = $aptObj->id; /** important or template won't work */
  $scope->rental = $orgAptObj = clone $aptObj; /** something (price breakdown) changes $aptObj */
  $scope->property_link = property_geolink($aptObj);

  if($host_id = $aptObj->host_id) {    
    $hostObj = get_user($host_id);
    $scope->host = $hostObj;
  }

  unset($aptObj->address_number);
  unset($aptObj->address_suffix);
  unset($aptObj->address_postcode);
  $scope->address = get_address_string($aptObj, ', ');

  /** Property Guide */    
  $descObjs = find_objects('property_description', ["property_id" => $aptObj->id, "active" => 1]);
  //dump($descObjs);
  $descriptions = array();
  $description = '';
  $description_more = '';
  
  
  foreach($descObjs as $descObj) {
    $type = $descObj->type;
    if($type == DESC_TYPE_PROPERTY) {
      if($descObj->site_id == $siteObj->id && $descObj->language == $__LANGUAGE) {
        $description = nl2br($descObj->description);
      } else {
        unset($descObj->id); // so we can save per site and language
        if(!$description) { // will be ignored or overwritten by above if correct site+language is found
          $description = nl2br($descObj->description);
          if($descObj->language != $__LANGUAGE) {
            $debug = "(Lang={$descObj->language} this={$__LANGUAGE})<br>";
            $debug =  '';
            $description = $debug.$description; 
          }
        }
      }
    } else {
      $descTypeObj = get_object('description_type', $type);
      if(!$descTypeObj->private) $description_more .= html_h4(phrase($descTypeObj->name, CAPITALIZE)).nl2br($descObj->description);
    }
    
    $descriptions[$descObj->type] = $descObj;
          
  }

  /** check avaialbility, including num_guests, min/max stay, changeover, etc */
  $scope->rate_average = 0;  
  $scope->discount_rate_average = 0;
  $scope->discount = '';
  $scope->description = $description.$description_more; /** used for public site */
  $scope->guides = $descriptions;
  
  if($in && $out) { /** search - get average rate */
    
    list($avail, $reason) = rental_availability($aptObj, ['in' => $in, 'out' => $out, 'ng' => $ng]);
    $scope->available = $avail;
    $scope->reason = $reason;
    $scope->rate_title = $aptObj->source_id == SOURCE_ID_INTERHOME ? "Approx." : "Average"; 

    
    $searchObj = array2obj($_GET, array('map' => 'urldecode'));
    $searchObj->in = $in;
    $searchObj->out = $out;
    $searchObj->t = $aptObj->type; 
    $searchObj->apt_id = $aptObj->id; 
    
    $city_id = $aptObj->city_id;
    $priceObj = get_average_rate($aptObj, $in, $out, $ng, true);
    
    print_log("Rate object for {$aptObj->name} in details:".dump($priceObj, true), 'property-search', LOG_LEVEL_TEST);
    
    $scope->rate = $priceObj;
    $scope->rate_average = $aptObj->rate_average = $avg = round($priceObj->average);
    $scope->rate_currency = $priceObj->currency;

    $scope->rate_unit = $rate_unit = 'night';
    if($priceObj->average_weekly) {
      $scope->rate_unit = $rate_unit = 'week';
      $scope->rate_average = round($priceObj->average_weekly);
    } elseif($priceObj->average_monthly) {
      $scope->rate_unit = $rate_unit = 'month';
      $scope->rate_average = round($priceObj->average_monthly);
    }
    
    if($priceObj->average_discounted) {
      $scope->discount = $aptObj->discount = $priceObj->discount;
      $scope->discount_rate_average = $aptObj->discount_rate_average = $priceObj->average_discounted;
    }
    
    $scope->price_breakdown = print_price_breakdown($aptObj, $priceObj);

    $scope->price_breakdown_link = 
      html_fancybox_link(
        ajax_operation_link('price-breakdown', $searchObj, array('public' => true)),  
        phrase('price_breakdown', CAPITALIZE), 
        array('class' => 'price-breakdown-link', 'data-url' => ajax_operation_link('price-breakdown', null, array('public' => true)), 'data-data' => array('t' => $t, 'apt_id' => $aptObj->id, 'in' => $in, 'out' => $out, 'ng' => $ng)));
      
    if(isset($_GET['foo'])) {
      echo("Average for $ng guests from $in to $out = $avg<br>");
      dump($priceObj);
    }

  } else {
    
    $currency = strtoupper($aptObj->currency);
    $rate = $aptObj->rate_day;
    if($currency != SYSTEM_CURRENCY) {
      $aptObj->rate_day = round(get_exchange_rate($currency, SYSTEM_CURRENCY, $rate));
      $aptObj->currency = SYSTEM_CURRENCY;
      print_log("{$aptObj->id} {$currency}{$rate} => {$aptObj->currency}{$aptObj->rate_day}", 'rental-rate', LOG_LEVEL_TEST);
      $scope->rental = $aptObj;
    }
    
    $scope->rate_currency = $aptObj->currency;
    $scope->rate_average = $aptObj->rate_average = $aptObj->rate_day;
  }
  
  /** used for single calendar */
  if($orgAptObj->discount_week) $orgAptObj->rate_week = 0; /** discount takes precedence over fixed rate */
  if($orgAptObj->discount_month) $orgAptObj->rate_month = 0; /** discount takes precedence over fixed rate */
  if($orgAptObj->discount_2_weeks) $orgAptObj->rate_2_weeks = 0; /** discount takes precedence over fixed rate */
  if($orgAptObj->discount_3_weeks) $orgAptObj->rate_3_weeks = 0; /** discount takes precedence over fixed rate */
  
  $rate_weekend = $aptObj->rate_weekend > 0 ? $aptObj->rate_weekend : $aptObj->rate_day;
  $scope->single_calendar_rental = 
    array("id" => $aptObj->id, 
          "name" => htmlspecialchars($aptObj->name, ENT_QUOTES), 
          "type" => $aptObj->type, 
          "host_id" => $aptObj->host_id,
          "owner_id" => $aptObj->owner_id, /** for historical reasons */
          "currency" => $aptObj->currency, "cur" => get_currency_symbol($aptObj->currency,true), 
          "rate_unit" => $rate_unit,
          "rate_day" => $orgAptObj->rate_day,            
          "rate_week" => $orgAptObj->rate_week, 
          "rate_2_weeks" => $orgAptObj->rate_2_weeks, 
          "rate_3_weeks" => $orgAptObj->rate_3_weeks, 
          "rate_month" => $orgAptObj->rate_month, 
          "rate_weekend" => $rate_weekend, 
          "rate_extraperson" => $aptObj->rate_extraperson ?: 0, 
          "rate_average" => $aptObj->rate_average ?: $aptObj->rate_day, 
          "discount_rate_average" => $aptObj->discount_rate_average ?: 0, 
          "rate_num_guests" => $aptObj->rate_num_guests ?: 2, 
          "discount_week" => $orgAptObj->discount_week, 
          "discount_2_weeks" => $orgAptObj->discount_2_weeks, 
          "discount_3_weeks" => $orgAptObj->discount_3_weeks, 
          "discount_month" => $orgAptObj->discount_month,
          "ng" => $ng, "in" => $in, "out" => $out, "nd" => $nd, "changeover" => $aptObj->changeover);    
  
  if(!$edit) { /** public details page */
    $mediaObjs = property_images($id) ?: explode(',', $aptObj->media);
    if($mediaObjs) {
      foreach($mediaObjs as $mediaObj) {
        $image = new stdClass;
        $image->src = print_media($mediaObj, array('size' => 'big', 'source_only' => true));
        $image->title = $mediaObj->name;
        $imageAr[] = $image;
      }
    }
    $scope->images = $imageAr;

    $scope->calendar = 1; // show availability calendar 
    
    $nearbyApts = location_find_nearest($t, $aptObj->location_lat, $aptObj->location_long, array('limit' => 4, 'exclude' => $aptObj->id));
    foreach($nearbyApts as $nearbyApt) {
      if($nearbyApt->currency != SYSTEM_CURRENCY) {
        $currency = $nearbyApt->currency; // just for logging
        $rate = $nearbyApt->rate_day; // just for logging
        $nearbyApt->rate_day = round(get_exchange_rate($nearbyApt->currency, SYSTEM_CURRENCY, $nearbyApt->rate_day));
        $nearbyApt->currency = SYSTEM_CURRENCY;
        print_log("nearby: {$nearbyApt->id} {$currency}{$rate} => {$nearbyApt->currency}{$nearbyApt->rate_day}", 'rental-rate', LOG_LEVEL_TEST);
      }
    }
    $scope->nearby_apts = $nearbyApts;

    if($siteObj->golf_site) {
      //echo("Got here ptype=$t nearbyapts=".count($scope->nearby_apts));
      $scope->nearby_golf = location_find_nearest('golf_club', $aptObj->location_lat, $aptObj->location_long, array('limit' => 4));
    }
    $scope->edit_link = $auth_edit ? property_edit_link($t, $id, true) : "";
    $scope->reviews = find_objects('feedback', array("apt_id" => $aptObj->id, "published" => 1));
    if(strip_blank($aptObj->quote)) {        
      $scope->quote = $aptObj->quote;
    } else {
      $quote = host_quote($aptObj->host_id, $id);
      $scope->quote = $quote ? $quote->quote : '';        
    }
    
    if($peak_exceptions = find_surcharge_exceptions($aptObj)) {    
      $exceptions = html_h4(phrase('exceptions', CAPITALIZE).':');
      $exceptions .= print_exceptions($aptObj->type, $id, $peak_exceptions);;
      $scope->description .= $exceptions; 
    }
    
  }
  
  
  $facAr = $aptObj->facilities ? explode(',', $aptObj->facilities) : array();
  $facs = array();
  foreach($facAr as $fac_id) {
    $facObj = new stdClass;
    $facObj->id = $fac_id;
    $facObj->name = get_object("facility", $fac_id, "name");
    $facObj->icon = rental_facility_icon($fac_id) ?: "fa fa-check";
    $facs[] = $facObj;
  }

  $scope->facs = $facs; // $scope->facilities = aptObj->facilities, already in use
  $scope->single_calendar_edit = $cal_edit = false;
  //$event = 'rental-calendar-events';
  $event = 'rental-calendar-availability';
  $scope->single_calendar_url = ajax_operation_link($event, array('id' => $id, 'edit' => 0), array('public' => true));
  $calOptions = array("selectable" => true, "editable" => false);
  
  if($in) $calOptions['defaultDate'] = $in;
  $scope->single_calendar_options = $calOptions;
  
  $today = today();      
  $yesterday = yesterday();      
  if($aptObj->calendar_startdate || $aptObj->calendar_startdate < $yesterday) {
    $res = rental_update_calendar($aptObj);
    if($res->success && is_array($res->data)) {
      $aptObj->calendar_availability = $res->data['calendar_availability'];
      $aptObj->calendar_startdate = $res->data['calendar_startdate'];
    }
  }

  
  $availabilty = [];
  if($aptObj->calendar_availability && $aptObj->calendar_startdate) {
    $offset = day_diff($aptObj->calendar_startdate, $today); // how many days ago
    $avail = substr($aptObj->calendar_availability, $offset);
    $length = strlen($avail);
    $blockedDates = [];
    if(strpos($avail, 'N') !== false) {
      //die("got here avail=$avail");
      $arr = str_split($avail);
      $d = $today;
      foreach($arr as $a) {
        if($a == 'N') $blockedDates[] = date(DATEPICKER_FORMAT_PHP, strtotime($d));
        $d = next_day($d);
      }
    }
    
    $availabilty = ["blocked_dates" => $blockedDates, "first" => $today, "last" => add_day($today, $length),  "length" => $length];
  } 
  
  if($changeover = $aptObj->changeover) {

    /** note - convert to 0=sun in JavaScript due to https://bootstrap-datepicker.readthedocs.io/en/latest/options.html#daysofweekdisabled */
    $wd = [0 =>'sun',1=>'mon',2=>'tue',3=>'wed',4=>'thu',5=>'fri',6=>'sat'];
    if($changeover == 7) $changeover = 0; 
    unset($wd[$changeover]);
    $availabilty["blocked_weekdays"] = array_keys($wd); // block these days for check-in 
    
  }
  
  $scope->availability = count($availabilty) ? $availabilty : '';

  $scope->data = array("t" => $t, "id" => $id, "reset"  => 1); // send to ajax fetch-template method and back to this controller
  
  return $scope;
}

function controller_rental_inquiry($siteObj, $pageObj, $options = array()) {  
  $options['request_type'] = 'inquiry';
  $scope = rental_booking_handler($siteObj, $pageObj, $options);
  
  $resObj = $scope->booking;
  switch($resObj->status) {
  case STATUS_DRAFT:
    break;
  case STATUS_INQUIRY:
    $scope->template = "rental-inquiry-success.html";
    break;
  default:
    break;
  }
  
  return $scope;
}

function controller_rental_request($siteObj, $pageObj, $options = array()) {
  $options['request_type'] = 'request';
  $scope = rental_booking_handler($siteObj, $pageObj, $options);

  $resObj = $scope->booking;
  switch($resObj->status) {
  case STATUS_DRAFT:
    break;
  case STATUS_REQUEST:
    $scope->template = "rental-request-success.html";
    break;
  default:
    break;
  }

  return $scope;
}

function controller_rental_booking($siteObj, $pageObj, $options = array()) {
  $options['request_type'] = 'booking';
  $scope = rental_booking_handler($siteObj, $pageObj, $options);
  return $scope;
}


/** common handler for inquiry/request/booking above*/
function rental_booking_handler($siteObj, $pageObj, $options = array()) {
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $obj_id = $slug = $scope->obj_id = $_SESSION['slug'] ?: $_SESSION['this_object_id'];
  if($slug) {
    $obj_type = pick_first($scope->property_type, $_SESSION['this_object_type'], $pageObj->property_type, $siteObj->property_type, 'shortstay');  
    $obj = $aptObj = $scope->rental = get_object($obj_type, $obj_id);
    if(!$obj) $scope->error = "Rental not found";
  } else {
    $scope->error = "Missing rental ID";
  }  
  
  if($scope->error) {
    $scope->template = '404';
    return $scope;
  }

  extract($_GET);
  $in  = $_GET['in'] ? date2sql($in) : '';
  $out = $_GET['out'] ? date2sql($out) : '';
  $ng  = $_GET['ng'] ?: 1;
  $res_id  = $_GET['rid'];
  
  if($res_id) {
    $resObj = get_object('reservation', $rid);
    // security
    $auth_res = auth_res($resObj);
    if($auth_res < USER_LEVEL_GUEST) return controller_error("Not authorized");    
  } elseif($in && $out && $ng) {
    $resData = search2res(['in' => $in, 'out' => $out, 'ng' => $ng, 'property_type' => $obj_type, 'apt_id' => $obj_id]);
    //echo("gh in=$in out=$out ng=$ng t=$obj_type id=$obj_id".dump($resData,true));
    if($error = $resData['error']) {
      $scope->error = $error;
    }

    $resObj = array2obj($resData);
  } else {
    return controller_error("Missing search parameters");
  }
  
  
  if($aptObj->source_id == SOURCE_ID_INTERHOME && $aptObj->guid) {
    
    $result = intherome_live_availability($aptObj->guid, strip_time($resObj->checkin), strip_time($resObj->checkout), $resObj->num_guests);
    print_log("Before Interhome Rate: {$resObj->currency} {$resObj->rate_base} Total: {$resObj->total} Fee: {$resObj->fee_service} GT: {$resObj->grand_total}", 'interhome', LOG_LEVEL_TEST);
    
    if($result->success) {
      $total = $result->total;
      $currency = $result->currency;
      $rate_day = $total / $resObj->num_days;
      $service_fee = service_fee($total);
      $dest_id = SOURCE_ID_INTERHOME;
      
      if($res_id) { /** no longer in use ? */
        if($total) update_object('reservation', array('rate_base' => $rate_day, 'currency' => $currency, 'fee_service' => $service_fee, 'dest_id' => $dest_id), $res_id);
        $resObj = get_object('reservation', $res_id); // reload
      } else {
        $resObj->currency = $currency;
        $resObj->rate_base = $rate_day;
        $resObj->total = $total;
        $resObj->fee_service = $service_fee;
        $resObj->grand_total = $total + $service_fee;
        $resObj->dest_id = $dest_id;
      }
      
      if(!$_SESSION['live']) $scope->messages = $result->message;
      $scope->source_services = $result->services;
      print_log("Ok, Interhome Rate: {$rate_day} Total: {$total} Fee: {$service_fee} GT: {$resObj->grand_total}", 'interhome', LOG_LEVEL_TEST);
    } else {
      $scope->source_error = $result->error ?: "Unknown error from Booking Partner";
      $ts = now();
      print_log("$ts: Interhome request failed: id:{$resObj->res_id} property:{$aptObj->id} in:".strip_time($resObj->checkin)." out:".strip_time($resObj->checkout)." guest:{$resObj->guest_id} Errors:".dump($result, true), 'interhome', LOG_LEVEL_ALWAYS);
    }
  }
  
 
  $scope->booking = $resObj;  
  $scope->search_url = $_SESSION['search_url'] ?: site_page_link($siteObj->id, PAGE_SHORTSTAY);
  $scope->feeArray = array('fee_service' => "Service Fee", 'fee_cleaning' => "Cleaning Fee", 'fee_booking' => "Booking Fee");
  
  return $scope;
  
  /** old
  $inputVars = $_GET ? $_GET : $_POST;
  $scope->search_url = $_SESSION['search_url'] ?: site_page_link($siteObj->id, PAGE_SHORTSTAY);
  
  if($inputVars) {
    extract($inputVars);  
    list($res_id, $booking_pin) = explode('-', $inputVars['r']);
  }
  
  if(!$u_id) {
    $scope->error = "Unauthorized";
    $scope->template = "404";
    return $scope;
  }
  
  if($_SESSION['slug']) {
    $res_id = $_SESSION['slug'];
    $resObj = get_object('reservation', $res_id);
    if(!auth_res($resObj)) $scope->error = "Unauthorized";
  } elseif($res_id && $booking_pin) {
    $resObj = get_object('reservation', $res_id);
    if($booking_pin != $resObj->booking_pin) {
      $scope->error = "Unauthorized";
    } elseif($resObj->guest_id && $resObj->guest_id != $u_id) {
      $scope->error = "Unauthorized";
    } elseif($resObj) {
      $resData = array('guest_id' => $u_id);
      $userObj = get_user($u_id);
      $address_fields = object_fields('address', false, true);
      foreach($address_fields as $f) $resData[$f] = $userObj->$f;
      list($res_id, $error) = update_object('reservation', $resData, $res_id); // set guest_id + name/address
      if($errors) dump($errors);
    }
  }
  
  if(!$resObj) $scope->error = "Missing reservation ID";
  $res_id = $resObj->res_id;
  $user_id = $scope->user_id = $u_id;
  
  $request_type = $options['request_type'];
  
  if($resObj->type == RES_TYPE_DIRECT && $request_type == 'request') redirect(site_page_link($siteObj->id, PAGE_BOOK)."?".get_query_string());
  elseif($resObj->type == RES_TYPE_REQUEST && $request_type == 'booking') redirect(site_page_link($siteObj->id, PAGE_REQUEST)."?".get_query_string());

  if($scope->error) return $scope;
  // check availability

  $apt_id = $aptObj->id;
  $ptype = $aptObj->type;

  $scope->rental = $aptObj = get_object($ptype, $apt_id);
  
  */
  
  /* if invoice already exists, we want to update */
  /**
  $inv_ids = add_reservation_invoices($res_id);
  if(!$inv_ids) {
    $scope->error = "Failed to created invoice";
    return $scope;
  }
  $resObj = get_object('reservation', $res_id); // reload to get service fee
  
  $inv_id = $inv_ids[0];
  $resObj->inv_id = $inv_id;
  $invObj = get_object('invoice', $inv_id);
  $scope->invoice = $invObj;
  $scope->invoice_id = $invObj->id;
  $scope->booking = $resObj;  
  //$scope->debug = dump($scope, true);
  
  $scope->feeArray = array('fee_service' => "Service Fee", 'fee_cleaning' => "Cleaning Fee", 'fee_booking' => "Booking Fee");

  // payment options 
  //ln -$_SESSION['live_payments_test'] = 1;
 	$live = $_SESSION['live'] || $_SESSION['live_payments_test'];

  //  set up Mollie, PayPal 
  $scope->paypal_key = $pp_key = get_config(($live ? "ppu" : "pput"), $siteObj->id);
  $scope->mollie_key = $mollie_key = get_config(($live ? "ml" : "mt"), $siteObj->id);
  $scope->mollie_methods = mollie_methods($mollie_key);    
  */
  
  return $scope;
}

function controller_dictionary($siteObj, $pageObj, $options = array()) {
  global $__header, $u_id, $__USER;
  $__header['end_scripts'][] = "/afr/bower/jquery-file-download/src/Scripts/jquery.fileDownload.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/jquery.base64.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/tableExport.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/locale/bootstrap-table-en-US.js"; /** todo: support other languages, use $_SESSION['locale']  */
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/export/bootstrap-table-export.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/editable/bootstrap-table-editable.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/editable/bootstrap-editable.js";

  $__header['css'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.css";
  $__header['css'][] = "/afr/bower/bootstrap-table/dist/extensions/editable/bootstrap-editable.css";


  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $errors = $messages = array();
  
  $obj_type = 'dictionary';

  $filters = array();
  $tbl = get_object_table($obj_type);

  //$filters["{$tbl}.site_id"] = [ATT_DEFAULT_NULL, $siteObj->id];  
  //$filters["{$tbl}.site_id"] = array('term' => ['!=', 'text_*'], 'site_id' => ['$or', [$siteObj->id, '$NULL']]);
  if($site_id = $_GET['site_id']) $filters["{$tbl}.site_id"] = $site_id;
  else $filters["{$tbl}.site_id"] = ['$or', [$siteObj->id, '$NULL']];
  //'language' => $language, 
   
  foreach(array('language','site_id') as $fld) {
    if($val = trim($_GET[$fld])) $filters[$fld] = $val;
  }
  
  if($__USER->user_level < USER_LEVEL_SYSTEM && $siteObj->id == 265)  $filters['site_id'] = $siteObj->id;
  
  $scope->filters = $filters;
  $filter_json = count($filters) ? json_encode($filters) : '';
  $scope->obj_type = $obj_type;
  $scope->data_url = "/admin/app_data.php?oper=get-rows&obj_type=$obj_type".($filter_json ? "&filters=".urlencode($filter_json) : '');
  $scope->edit_url = "/admin/app_data.php?oper=save&obj_type=$obj_type";
  $scope->title = "Dictionary";
    
  return $scope;
}

function controller_users($siteObj, $pageObj, $options = array()) {
  global $__header, $u_id;
  $__header['end_scripts'][] = "/afr/bower/jquery-file-download/src/Scripts/jquery.fileDownload.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/jquery.base64.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/tableExport.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/locale/bootstrap-table-en-US.js"; /** todo: support other languages, use $_SESSION['locale']  */
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/export/bootstrap-table-export.js";
  $__header['css'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.css";

  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $errors = $messages = array();
  $client_id = $scope->client_id = $_SESSION['client_id'];
  $client_name = $client_id ? get_object('client', $client_id, 'name') : '';
  
  $obj_type = $options['obj_type'] ?: 'user';

  $filters = array();
  $tbl = get_object_table($obj_type);
  $filters["{$tbl}.client_id"] = $client_id;
  foreach(array('user_level','org_id','start','end') as $fld) {
    if($val = trim($_GET[$fld])) {
      switch($fld) {
      case 'start':
        $filters['created'] = array(">=", date2sql($val));
        break;
      case 'end':
        $filters['created'] = array("<=", date2sql($val));
        break;
      case 'user_level':
        $filters['user_level'] = array("=", $val);
        break;
      default:
        $filters[$fld] = $val;
        break;
      }
    }
  }
  
  $scope->filters = $filters;
  $filter_json = count($filters) ? json_encode($filters) : '';
  $scope->obj_type = $obj_type;
  $scope->data_url = "/admin/app_data.php?oper=get-rows&obj_type=$obj_type".($filter_json ? "&filters=".urlencode($filter_json) : '');
  $scope->title = ucfirst($obj_type)."s ".($client_id ? " for $client_name" : "");
    
  return $scope;
}

function controller_backend($siteObj, $pageObj, $options = array()) {
  global $u_id, $u_level,$__header, $__CLASS_FLAGS;
  $__header['end_scripts'][] = "/afr/bower/jquery-file-download/src/Scripts/jquery.fileDownload.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/jquery.base64.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/tableExport.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/locale/bootstrap-table-en-US.js"; /** todo: support other languages, use $_SESSION['locale']  */
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/export/bootstrap-table-export.js";
  $__header['css'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.css";

  $limit = 50;

  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;  
  $scope->class_flags = $__CLASS_FLAGS;
  $obj_type = $_GET['obj_type'];
  
  $classes = array();
  if($u_level < USER_LEVEL_ADMIN) return controller_error("Not authorized", 401);
  $scope->classes = $classes = admin_menu_items($siteObj, $options);  
  
  if($obj_type) {
    $scope->obj_type = $obj_type;
    $scope->obj_name = get_object_name($obj_type);
    $scope->obj_key = get_object_key($obj_type);
    
    if($classObj = get_object('class', $obj_type, '', array('ignore_filters' => 1))) { /** read from db */
      $scope->class_def = $classObj;
      $scope->class_attributes = find_objects('attribute', array('class' => $obj_type));
      $scope->class_security = find_objects('security', array('node' => $obj_type));
    }
    
    /** read from file, disabled 
    $class_found = false;
    if($class_header = get_class_header($obj_type)) { 
      $class_found = true;
      $class_user_level = $class_header[CLASS_USER_LEVEL];
    }
    */
   
    $actions = array('view', 'list', 'add', 'edit', 'del', 'copy');
    
    foreach($actions as $ac) {
      $key = 'auth_'.$ac;
      $scope->$key = auth_action($obj_type, $ac);
    }
    if(!$classObj) {
      $scope->error = "$obj_type not found";
      return $scope;
    } elseif($classObj->user_level > $u_level) {
      $scope->error = "Not authorized (User level)";
      return $scope;
    } elseif(!$scope->auth_list) {
      $scope->error = "Not authorized (List)";
      return $scope;
    }
    $class_def = get_class_def($obj_type);
    $class_fields = $class_def->fields;
    $fields = array();
    foreach($class_fields as $field => $attributes) {
      if(!($attributes[ATT_FLAGS] & AF_HIDE_LIST)) $fields[$field] = $attributes[ATT_NAME];      
    }
    $scope->fields = $fields;
    $scope->data_url = "/admin/app_data.php?oper=list&obj_type=$obj_type&limit=$limit";
        
    //$scope->auth_add = auth_action($obj_type, 'add');
  } else {
    //$scope->classes = get_classes();
  }
  //dump($items);
  
  return $scope;
}

function controller_rentals($siteObj, $pageObj, $options = array()) {
  global $__header, $u_id, $u_level;
  
  $__header['end_scripts'][] = "/afr/bower/jquery-file-download/src/Scripts/jquery.fileDownload.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/jquery.base64.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/tableExport.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/locale/bootstrap-table-en-US.js"; /** todo: support other languages, use $_SESSION['locale']  */
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/export/bootstrap-table-export.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/editable/bootstrap-table-editable.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/editable/bootstrap-editable.js";
  $__header['css'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.css";  
  $__header['css'][] = "/afr/bower/bootstrap-table/dist/extensions/editable/bootstrap-editable.css";

  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $errors = $messages = array();
  $client_id = $scope->client_id = $_SESSION['client_id'];
  $client_name = $client_id ? get_object('client', $client_id, 'name') : '';
  $ptype = $scope->property_type = pick_first($siteObj->property_type, $_SESSION['property_type'], "shortstay");
  $filters = array();
  $filters['client_id'] = $client_id;
  $system_user = 0;
  $host_ids = user_host_list($u_id) ?: array();

  if($u_level >= USER_LEVEL_STAFF) {
    $system_user = $scope->system_user = 1;
    $host_ids = array();
  } elseif(count($host_ids)) { 
    $filters['host_id'] = $host_ids;
  } else {
    $scope->error = "You are not a host, and not authorized to manage any hosts";
    return $scope;
  }
  
  $obj_type = $ptype;

    
  /** handle filters */
  if(!isset($_GET['active'])) $_GET['active'] = 1;
  foreach(array('active','host_id','address_country') as $fld) {
    if(isset($_GET[$fld]) && strlen($_GET[$fld])) {
      $val = trim($_GET[$fld]);
      switch($fld) {        
        default:
          $filters[$fld] = $val;
          break;
      }
    }
  }  

  $host_id = count($host_ids) == 1 ? $host_ids[0] : $filters['host_id'];
  if($host_id) $client_name = user_display_name($host_id);
  if($cc = $filters['address_country']) $client_name .= " in ".find_object('countries', array('id' => $cc), 'name');

  //dump($filters);
  $scope->count = $count = count_objects($obj_type, $filters);
  
  if(!$host_ids) {
    $host_ids = find_objects($obj_type, $filters, array("field" => "distinct host_id"));
  }
  
  $scope->countries = $countries = find_objects($obj_type, $filters, array("field" => "distinct address_country"));
  $scope->user_level = $u_level;
  $scope->host_ids = $host_ids;
  $scope->filters = $filters;
  $filter_json = count($filters) ? json_encode($filters) : '';
  $scope->obj_type = $obj_type;
  $obj_name = get_object_name($obj_type);
  $scope->data_url = "/admin/app_data.php?oper=get-rows&obj_type=$obj_type".($filter_json ? "&filters=".urlencode($filter_json) : '');
  $scope->edit_url = "/admin/app_data.php?oper=save&obj_type=$obj_type";
  $scope->title = $obj_name."s ".($client_id ? " for $client_name" : "")." ({$count})";
  
  return $scope;
}

function controller_payments($siteObj, $pageObj, $options = array()) {
  redirect_secure();
  $options['obj_type'] = 'payment';
  $scope = controller_invoices($siteObj, $pageObj, $options);
  return $scope;
}

function controller_payouts($siteObj, $pageObj, $options = array()) {
  redirect_secure();
  $options['obj_type'] = 'withdrawal';
  $scope = controller_invoices($siteObj, $pageObj, $options);
  return $scope;
}

function controller_invoices($siteObj, $pageObj, $options = array()) {
  redirect_secure();
  global $__header, $u_id, $u_level;
  
  $__header['end_scripts'][] = "/afr/bower/jquery-file-download/src/Scripts/jquery.fileDownload.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/jquery.base64.js";
  $__header['end_scripts'][] = "/afr/bower/table-export/tableExport.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/locale/bootstrap-table-en-US.js"; /** todo: support other languages, use $_SESSION['locale']  */
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/export/bootstrap-table-export.js";
  $__header['css'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.css";

  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $errors = $messages = array();
  $client_id = $scope->client_id = $_SESSION['client_id'];
  $client_name = $client_id ? get_object('client', $client_id, 'name') : '';
  $host_ids = user_host_list($u_id) ?: array();
  $ptype = pick_first($siteObj->property_type, $_SESSION['property_type'], "shortstay");
  $filters = array();
  $filters['client_id'] = $client_id;
  $system_user = 0;
  if($u_level == USER_LEVEL_SYSTEM) {
    $system_user = $scope->system_user = 1;
  } elseif(count($host_ids)) { 
    $filters['host_id'] = $host_ids;
  } else {
    $scope->error = "You are not a host, and not authorized to manage any hosts";
    return $scope;
  }
  
  $obj_type = $options['obj_type'] ?: 'invoice';
  if(!in_array($obj_type, array('invoice', 'payment', 'withdrawal'))) {
    $scope->error = "Invalid class $obj_type";
    return $scope;
  }
  
  switch($obj_types) {
    case "invoice";
    break;
    case "payment";
    break;
    case "withdrawal";
    break;    
  }
  /** handle filters */
  foreach(array('status','org_id','start','end', 'payment_type', 'payment_status', 'sender_id', 'recipient_id', 'currency', 'host_id') as $fld) {
    if($val = trim($_GET[$fld])) {
      switch($fld) {        
        case 'start':
          $filters['sent_date'] = array(">=", date2sql($val));
          break;
        case 'end':
          $filters['sent_date'] = array("<=", date2sql($val));
          break;
        case 'status':
          $filters['status'] = array("=", $val);
          break;
        case 'payment_status':
          $filters['payment_status'] = array(">=", $val);
          break;
        default:
          $filters[$fld] = $val;
          break;
      }
    }
  }
  
  if($_GET['start'] && $_GET['end']) $filters['sent_date'] = array("><", date2sql($_GET['start']), date2sql($_GET['end']));  
  //echo("type=$obj_type".dump($filters, true));
  
  $scope->filters = $filters;
  $filter_json = count($filters) ? json_encode($filters) : '';
  $scope->obj_type = $obj_type;
  $obj_name = get_object_name($obj_type);
  $scope->data_url = "/admin/app_data.php?oper=get-rows&obj_type=$obj_type".($filter_json ? "&filters=".urlencode($filter_json) : '');
  $scope->title = $obj_name."s ".($client_id ? " for $client_name" : "");
  
  if(in_array($obj_type, array('payment', 'invoice'))) {
    $org_ids = find_objects($obj_type, array('client_id' => $client_id), array('fields' => 'distinct org_id'));
    $scope->org_ids = array_filter($org_ids);
  } else { // Payouts
    
    /** Filters from form */
    $scope->host_id = $host_id = $_GET['host_id'] ?: 0;
    $scope->currency = $currency = $_GET['currency'] ?: $currencies[0];
    if($host_id) {
      $scope->host = $hostObj = get_user($host_id);
      $scope->host_name = $host_name = get_user_name($hostObj);
    }

    $scope->title = "Past Payouts";
    //if($filters['recipient_id']) $search['recipient_id'] = $recipient_id;
    //if($filters['currency']) $search['payment_currency'] = $currency;  // todo chooser  


    /** Outstanding Payments */
    $search = array();
    if(!$system_user) $search['host_id'] = $host_ids;  
    
    if($start = $_GET['ostart']) $search['created'] = array(">=", date2sql($start));
    if($end = $_GET['oend']) $search['created'] = array("<=", date2sql($end));

    $search['client_id'] = $client_id;
    $search['gateway_id'] = GATEWAY_PAYPAL;
    $search['payment_status'] = array(PAYMENT_STATUS_COMPLETED, PAYMENT_STATUS_PARTIALLY_REFUNDED);  
    $search['payment_type'] = array(PAYMENT_TYPE_CREDIT_CARD, PAYMENT_TYPE_PAYPAL, PAYMENT_TYPE_CREDIT_CARD_CAPTURE, PAYMENT_TYPE_ECHECK, PAYMENT_TYPE_REFUND);  
    //$search['payment_net'] = array('>=', INV_TOLERANCE);  
    $search['tx_id'] = array('>', 0);    
    $search['withdrawal_id'] = array('=', ATT_DEFAULT_NULL);  // todo: this excludes partial withdrawals

    //$scope->currencies = $currencies = find_objects("payment", $search, array("fields" => "distinct(payment_currency) as currency"));
    $scope->currencies = $currencies = array("" => "Select Currency...", "EUR" => "Euro", "USD" => "US Dollars");

    $hostsAr = array();
    $hostsAr[0] = "Select...";
    

    $tbl = get_object_table('user');
    $user_fields = array("{$tbl}.id", 'concat(user_profile.first_name, " ", user_profile.last_name) as name'); 

    if($host_ids = find_objects('payment', $search, array('fields' => "distinct host_id"))) {
      $hosts = find_objects('user', array("{$tbl}.id" => $host_ids), array('fields' => $user_fields));
      foreach($hosts as $host) $hostsAr[$host->id] = $host->name;
      $scope->outstanding_hosts = $hostsAr;
    }

    if($host_id) $search['host_id'] = $host_id;    
    if($currency) $search['payment_currency'] = $currency;
    
    $search_json = json_encode($search);    
    $scope->outstanding_url = "/admin/app_data.php?oper=get-rows&obj_type=payment&filters=".urlencode($search_json);
    
    /** Outstanding Corrections and Transfers */
    $search = array();
    if(!$system_user) $search['host_id'] = $host_ids;    
    $search['client_id'] = $client_id;
    // $search['payment_status'] = array(PAYMENT_STATUS_COMPLETED, PAYMENT_STATUS_PARTIALLY_REFUNDED);  
    //$search['payment_type'] = array(PAYMENT_TYPE_TRANSFER, PAYMENT_TYPE_CORRECTION);  
    $search['payment_type'] = PAYMENT_TYPE_CORRECTION;  
    //$search['payment_net'] = array('>=', INV_TOLERANCE);  
    $search['withdrawal_id'] = array('=', ATT_DEFAULT_NULL);  // todo: this excludes partial withdrawals
    if($host_id) $search['host_id'] = $host_id;
    if($currency) $search['payment_currency'] = $currency;

    $search_json = json_encode($search);    
    $scope->correction_url = "/admin/app_data.php?oper=get-rows&obj_type=payment&filters=".urlencode($search_json);
    
    $hostsAr = array();
    $hostsAr[0] = "Select Host...";
    if($scope->host_ids = $host_ids = find_objects('property', array('client_id' => $client_id, 'type' => $ptype, 'active' => 1), array('fields' => "distinct host_id"))) {
      $hosts = find_objects('user', array("{$tbl}.id" => $host_ids), array('fields' => $user_fields));
      foreach($hosts as $host) $hostsAr[$host->id] = $host->name;
      $scope->hosts = $hostsAr;
    }
    if($system_user) $scope->paypal_balance = $balance = paypal_get_balance();
    
  }
  
  return $scope;
}

function controller_dashboard($siteObj, $pageObj, $options = array()) {
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;

  $inbox_scope = controller_inbox($siteObj, $pageObj, $options);
  $scope->threads = $inbox_scope->threads;
  
  if($siteObj->property_site) {
    $bookings_scope = controller_bookings($siteObj, $pageObj, $options);
    foreach($bookings_scope as $k => $v) $scope->$k = $v;
  }
  
  //$scope->debug = "Dashboard: Coming soon!";
  return $scope;
}

function controller_bookings($siteObj, $pageObj, $options = array()) {
  global $u_id, $u_level, $__header;
  
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.js";
  $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/locale/bootstrap-table-en-US.js"; /** todo: support other languages, use $_SESSION['locale']  */
  
  //$__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/editable/bootstrap-table-editable.js";
  //$__header['end_scripts'][] = "/afr/bower/x-editable/dist/bootstrap3-editable/js/bootstrap-editable.js";
  
  $__header['css'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.css";

    
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  redirect_secure();
  
  //echo("Scope:".dump($scope,true));die();
  $errors = $messages = array();

  $slug = $_SESSION['slug'];  
  $obj_type = $scope->obj_type = "reservation"; 
  
  $all_hosts = 0;
  if($u_level >= USER_LEVEL_STAFF) {
    $host_id = $slug ?: 0;
    if($host_id && !get_user($host_id)) return controller_error("User {$slug} not found");    
  } elseif($u_level >= USER_LEVEL_HOST) {
    $host_id = $slug ?: $u_id;
    $host_ids = user_host_list($u_id);
    if($host_id != $u_id && in_array($host_id, $host_ids)) return controller_error("User {$slug} not authorized");
  } else {
    $host_id = $u_id;
  }
  
  $inline = $pageObj->page_type == PAGE_DASHBOARD;

  // my bookings - or that of user in slug - or all bookings (if staff and no slug)
  $search = array("res_id" => ['>', 0], "type" => ['>', RES_TYPE_ADMIN], "status" => ['!=', [STATUS_DRAFT, STATUS_BLOCKED]]);
  //$search['paid'] = ['>', 0];
  
  if($host_id) $search['host_id'] = $host_id; 

  if($inline) {
    $start = $scope->start = $_GET['start'] ?: 0;
    $limit = $scope->limit = 50;
    $searchOptions = array("fields" => $fields, "start" => $start, "limit" => $limit);
    
    $bookings = find_objects("reservation", $search, $searchOptions);
    $scope->booking_count = count_objects("reservation", $search);
    
    foreach($bookings as $k => $booking) {
      $booking->chat_count = count_objects('chat', ['parent_type' => "reservation", 'parent_id' => $booking->res_id]);;
      $bookings[$k] = $booking;
    }  
    $scope->bookings = $bookings;
  } else {
    $scope->bookings_url = "/admin/app_data.php?oper=get-rows&obj_type=reservation&filters=".urlencode(json_encode($search));
  }
  
  //$scope->booking_count = count($bookings);

  // my trips
  $search = array("guest_id" => $u_id, "status" => ['!=', STATUS_DRAFT]);
  if($inline) {
    $fields = array('res_id','created','status','city_id','city_name','checkin','checkout','apartment_name','currency','grand_total', 'chat_count');
    $start = $scope->start = $_GET['start'] ?: 0;
    $limit = $scope->limit = 50;
    $searchOptions = array("fields" => $fields, "start" => $start, "limit" => $limit);
    $trips = find_objects("reservation", $search, $searchOptions);
    foreach($trips as $k => $trip) {
      $trip->chat_count = count_objects('chat', ['parent_type' => "reservation", 'parent_id' => $trip->res_id]);;
      $trips[$k] = $trip;
    }
    $scope->trips = $trips;
    $scope->trip_count = count_objects("reservation", $search);
  } else {
    $scope->trips_url = "/admin/app_data.php?oper=get-rows&obj_type=reservation&filters=".json_encode($search);
  }
  
  return $scope;
}

/** no security (used in mail templates called from crontab) - copy to booking_status 
    fetch booking, rental, guest, host */
function controller_booking($siteObj, $pageObj, $options = array()) {
  global $u_id, $u_level;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $errors = $messages = array();

  $obj_type = $scope->obj_type = "reservation"; 
  $obj_id = $res_id = $scope->obj_id = $scope->res_id = pick_first($scope->res_id ?: $scope->obj_id, $_GET['res_id'] ?: $_GET['obj_id'], $options['res_id'] ?: $options['obj_id'], $_SESSION['this_object_id']);
  $obj = $resObj = $res_id ? get_object($obj_type, $obj_id) : ''; // force reload     

  if(!$resObj) {
    $errors[] = "Booking {$obj_id} not found"; 
    $scope->error = $errors;
    return $scope;
  }
  
  
  $status = $resObj->status;
  $apt_id = $resObj->apt_id;
  $property_type = $resObj->property_type;
  $aptObj = ($apt_id && is_property_type($property_type)) ? get_object($property_type, $apt_id) : null;    
  if(!$aptObj) {$errors[] = "Rental not found"; $scope->error = $errors; return $scope;}
  
  $pin = $scope->pin_code = pick_first($_GET['pin'], $options['pin'], $scope->pin, $scope->pin_code);

  $scope->host_id = $host_id = $obj->host_id;
  $scope->is_host = $is_host = $u_id && $host_id && $u_id == $host_id;
  $scope->guest_id = $guest_id = $obj->guest_id;
  $scope->is_guest = $is_guest = $u_id && $guest_id && $u_id == $guest_id;
  $hostObj = $host_id ? get_user($host_id) : null;
  
  if($guest_id) {
    $guestObj = get_user($guest_id);
  } else {
    $guestObj = new stdClass;
    $keys = array('salutation', 'first_name', 'last_name', 'email_address', 'cell_phone', 'city', 'country');
    foreach($keys as $key) $guestObj->$key = $resObj->$key;
    $guestObj->display_name = get_name_string($guestObj);
  }
  
  $scope->id = $res_id = $resObj->res_id;
  $scope->rental = $aptObj;
  $scope->booking = $resObj;
  $scope->guest = $guestObj;
  $scope->host = $hostObj;
  $scope->public_link = booking_link($resObj);
  $scope->pin = $pin;

  $scope->type_name = booking_type_name($resObj); 
      
  return $scope;
}
  
function controller_booking_status($siteObj, $pageObj, $options = array()) {
  global $u_id, $u_level, $__header;
  $ver = $_SESSION['version'] ?: date('md');
  if($u_level >= USER_LEVEL_STAFF) $__header['end_scripts'][] = "/afr/js/admincal-dialog.js?v=$ver"; 
  $scope = controller_booking($siteObj, $pageObj, $options);
  if($scope->error) return $scope;
  
  $resObj = $scope->booking;
  $res_id = $resObj->res_id;
  $is_host = $scope->is_host;
  $is_guest = $scope->is_guest;
  
  
  /** keep */
  redirect_secure();
  
  $pin = pick_first($_GET['pin'], $options['pin'], $scope->pin, $scope->pin_code);
  
  if($u_id) { // we're logged in 
    $user_id = $u_id;
    $auth_level = auth_res($resObj);
  } elseif($pin) { // check pin
    $scope->pin_code = $pin;
    $auth_level = myhash($resObj->booking_pin) == $pin ? USER_LEVEL_GUEST : 0;
    if(!$auth_level) $auth_level = myhash_old($resObj->booking_pin) == $pin ? USER_LEVEL_GUEST : 0; // grandfather clause
    if(!$auth_level) {
      $scope->error = "Invalid PIN";
      $scope->template = '403';
      $pin = '';
      return $scope;
    }
  } else { // redirect to login
    $link = page_link(PAGE_LOGIN)."?ref=".urlencode(this_path());
    $scope->error = phrase('please log in', CAPS).html_break().html_link($link, phrase('click here'));
    $scope->redirect = $link;
    return $scope;
  }
  
  print_log("res_id:{$res_id} pin:{$pin} auth:{$auth_level}", 'booking', LOG_LEVEL_TEST);
  
  $scope->auth_level = $auth_level;
  $scope->auth_edit = $auth_edit = $auth_level > 0; // can edit?
  if(!$auth_level) {
    $scope->error = "Not authorized";
    $scope->template = '403';
    return $scope;
  }  
  
  $scope->data = array_filter(array("obj_type" => 'reservation', "res_id" => $res_id, "pin"  => $pin)); // send to ajax fetch-template method and back to this controller (in options)
  $scope->is_admin = $is_admin = $u_level >= USER_LEVEL_ADMIN;
  $scope->can_cancel = ($is_guest && in_array($status, [STATUS_INQUIRY, STATUS_REQUEST, STATUS_PROPOSED, STATUS_PENDING, STATUS_RESERVED, STATUS_COMPLETE])) || 
                       ($is_host && in_array($status, [STATUS_PROPOSED, STATUS_PENDING, STATUS_RESERVED, STATUS_COMPLETE])) || 
                       $is_admin;  
  
  $scope->can_alter = 0; /** todo: implement */
  
  
  /** This processing also takes place in crontab (hourly) */
  if($resObj->expires && $resObj->expires < now()) { // expire booking
    list($id, $errors) = update_object('reservation', array('status' => STATUS_EXPIRED), $resObj->res_id);
    $resObj = get_object('reservation', $resObj->res_id);    
  }
  
  if($auth_edit) {
    $misArray = reservation_invoice_mismatch($resObj, array('values' => 1));
    if($difference = $misArray['difference']) {
      $scope->mismatch = $misArray;
    }      
  }    
  
  if($errors) {
    $scope->error = $errors;
    $scope->template = "403";    
    return $scope;
  }
    
  //$scope->rate_box = print_rate_box($resObj, $is_host ? USER_LEVEL_OWNER : USER_LEVEL_GUEST); /** get rid of */
  $scope->uploader = object_media_uploader("reservation", $res_id, 'upload');
  
  /** template specific */
  $scope->view = $template = pick_first($_GET['view'], $_GET['template'], $options['template'], "_booking-status-overview.html");
  if($template && strpos($template, '_booking-status-') === false) $template = $scope->view = "_booking-status-{$template}.html"; // allow shortform
  
  switch($template) {
    case "_booking-status-overview.html":
      // find invoices and payments
      $invSearch = array();
      $invSearch['parent_type'] = 'reservation';
      $invSearch['parent_id'] = $res_id;  
      $invSearch['status'] = array('>=', INV_STATUS_DRAFT);
      //$fields = array('invoice.id', 'invoice_id', 'type', 'status', 'start_date', 'end_date');
      $scope->invoices = $invObjs = find_objects('invoice', $invSearch, array('sort' => 'type, start_date'));
      $scope->inv_id = $inv_id = count($invObjs) ? $invObjs[0]->id : 0;
      $scope->invoice = $inv_id ? get_object('invoice', $inv_id) : null;
      
      if($auth_level >= USER_LEVEL_STAFF) {
        $scope->change_log = object_change_log($obj_type, $obj_id);
        $scope->mail_log = object_mail_log($obj_type, $obj_id);
      }
      
      //dump($invObjs);
      break;
    case "_booking-status-edit.html":
      break;
      
    case "_booking-status-payment.html":
      break;
    case "_booking-status-feedback.html":
      if($feedback = find_object("feedback", array("parent_type" => "reservation", "parent_id" => $resObj->res_id))) {
        // show existing feedback
        $scope->feedback = $feedback;
        $scope->foo = 'found';

      } elseif($auth_edit) { // show form
        $scope->foo = 'yes';
        $scope->purpose = get_objects_assoc("feedback_purpose", "", array('first' => phrase('select', CAPITALIZE)));
        $scope->profile = get_objects_assoc("feedback_profile", "", array('first' => phrase('select', CAPITALIZE)));
      } else {
        $scope->foo = 'not';
      }
      break;
    case "_booking-status-chat.html":
      $host_id = $resObj->host_id;
      $guest_id = $resObj->guest_id ?: "reservation_".$resObj->res_id;
      
      $scope->sender_id = $user_id;
      $scope->receiver_id = $user_id == $resObj->host_id ? $guest_id : $host_id;
      $scope->parent_type = "reservation";
      $scope->parent_id = $resObj->res_id;
      $scope->user_ids = [$guest_id, $host_id];
      $scope->thread = find_objects("chat", array("parent_type" => "reservation", "parent_id" => $resObj->res_id));
      //dump($scope->chat);
      break;
          
    case "_booking-status-itinerary.html": /** itinerary */
      $scope->pdf_url = create_pdf_booking($resObj); // always create fresh PDF on view
      break;
      
    case "_booking-status-send.html": /** proposal */
      if(!in_array($resObj->status, array(STATUS_PROPOSED, STATUS_RESERVED, STATUS_COMPLETE))) {
        $scope->error = "Invalid reservation status";
        $scope->template = '403';
        return $scope;
      }

      list($guest_text, $host_text, $staff_text) = booking_mail_message($resObj);
      
      
      //$mail_scope = ['profile_id' => $resObj->host_id,
      //               'booking' => $resObj, 
      //               'rental' => $aptObj, 
      //               'receiver_name' => $guest_name, 
      //               'receiver_role' => 'guest', 
      //               'receiver_id' => $resObj->guest_id, 
      //               'main_message' => $guest_text];
      //$scope->mail_scope = $mail_scope;            
      
      $scope->mail_template = $template = "mail/mail-booking";    
      $scope->mail_controller = $controller = "booking_status";            
      
      //$body = smarty_mail_template($siteObj, $template, ['scope' => $mail_scope, 'controller' => $controller]);
      //echo("body = $body");
      $scope->mail_action = '';            
      
      $mail = new stdClass;
      
      $mail->from = site_email($resObj->site_id, true) ?: site_email($siteObj);    
      $mail->subject = mail_subject('reservation', $resObj);
      $mail->main_message = $guest_text;

      $guest_name =  $resObj->guest_id ? get_user_name($resObj->guest_id) : get_name_string($resObj);
      $mail->recipient = $mail->to = guest_email($resObj, true) ?: email_recipient($resObj->email_address, $guest_name);    
      $mail->receiver_role = 'guest';
      $mail->receiver_id = $resObj->guest_id;

      $mail->obj_name = 'booking';
      $mail->obj_type = 'reservation';
      $mail->obj_id = $resObj->res_id;
      
      //$mail->body = $body;
      $mail->template = $template;
      $mail->controller = $controller;
      $scope->mail  = $mail; 

      break;

    case "_booking-status-recalculate.html":
      print_log("recalc:", 'invoice', LOG_LEVEL_TEST);
      
      $search = array('res_id' => $res_id, 'status' => array('>=', INV_STATUS_DRAFT));
      $fields = array('invoice.id', 'invoice_id', 'start_date', 'end_date', 'total', 'paid', 'balance', 'sequence', 'locked', 'concerning');
      $options = array('fields' => $fields, 'sort' => 'sequence', 'debug_query' => 0);
      $scope->before = $before = find_objects('invoice', $search, $options);
      $all_ids = [];
      foreach($before as $invObj) $all_ids[] = $invObj->id;
      //foreach($before as &$invObj) $invObj->concerning = "foo";
      //$message = html_h2('before').invoice_debug_print($res_id);
      
      
      $inv_ids = add_reservation_invoices($res_id);
      //dump($inv_ids);
      if($inv_ids === false) {
        $scope->error = "Failed to recalcuate invoices - is this a booking from a remote source? ";
      } else {
        foreach($all_ids as $inv_id) recalculate_invoice($inv_id);
        //$invObjs = find_reservation_invoices($res_id, array('search' => array('type' => INV_TYPE_BOOKING, 'status' => array('>=', STATUS_ALL))));
        //$inv_ids = array_find_key($invObs, 'id');
        
        $scope->after = $after = find_objects('invoice', $search, $options);     
        
        /** calc extras - from update_invoice_total */
        $count = count($all_ids);
        $inv_id_list = $count ? implode(',', $all_ids) : '';
        print_log("recalc: count=$count list=$inv_id_list for $res_id", "invoice", LOG_LEVEL_ALWAYS);  
        if($count) {
          $extra_li_types = implode(',', array(LI_TYPE_PRODUCT, LI_TYPE_SERVICES, LI_TYPE_EXTRAS, LI_TYPE_CATERING));
          $qs = "SELECT sum(total) FROM inv_lineitem WHERE inv_id IN ($inv_id_list) AND type IN ($extra_li_types)";
          $extras = db_getOne($qs); 
          print_log("recalc: update_invoice_total: other charges=$extras from $inv_id_list for $res_id", "invoice", LOG_LEVEL_ALWAYS);  
          print_log("qs: $qs", "invoice", LOG_LEVEL_ALWAYS);  
          db_query("UPDATE reservation SET other_charges = '$extras' WHERE res_id=$res_id");
          update_reservation_total($res_id);
        }
        
        $resObj = $scope->booking = get_object('reservation', $res_id);
        
      }
       
    case "_booking-status-recalculate.html":
      break;

    case "_booking-status-cancel.html":
      if(!$is_host && !$is_guest && !$is_admin) {
        $scope->error = "Only guest and host can cancel a booking";
        $scope->template = "404";
      }
      break;

    default:
      break;
  }
  
  return $scope;
}

function controller_payment($siteObj, $pageObj, $options = array()) {
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $options['template'] = "_payment-overview.html";
 
  /** normally we use invoice ID, but for mails, we pass payment ID */
  if($payment_id = $scope->payment_id) {
    $paymentObj = get_object('payment', $payment_id);
    $scope->inv_id = $paymentObj->inv_id;
    $options['scope'] = $scope;
  }
  
  $scope = controller_invoice($siteObj, $pageObj, $options); // much the same
  if($paymentObj) $scope->payment = $paymentObj;
  if($scope->error || $scope->redirect) return $scope;
 
  //echo("gh scope=".dump($scope,true));
  return $scope;
}

/** todo: splid controller_invoice and invoice_status */

function controller_invoice($siteObj, $pageObj, $options = array()) {
  global $__header, $u_id, $u_level, $__LIVE;
  $__header['end_scripts'][] = "/afr/bower/jquery-file-download/src/Scripts/jquery.fileDownload.js";
  $__header['css'][] = "/afr/css/print.css";

  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;  
  $errors = $messages = array();
  $obj_type = $scope->obj_type = "invoice"; 
  $obj_id = $inv_id = $scope->obj_id = $scope->inv_id = pick_first($scope->inv_id ?: $scope->obj_id, $_GET['inv_id'] ?: $_GET['obj_id'], $options['inv_id'] ?: $options['obj_id'], $_SESSION['this_object_id']);
  $pin = pick_first($_GET['pin'], $options['pin'], $scope->pin, $scope->pin_code);
  $obj = $invObj = $inv_id ? get_object($obj_type, $obj_id) : '';  

  print_log("ctrl invoice inv_id={$inv_id} pin={$pin} id: {$invObj->id}", 'invoice', LOG_LEVEL_TEST);
  redirect_secure();
  
  //die("u_id=$u_id Auth_level = $auth_level inv_id=$inv_id");
  //echo("ot=$obj_type id=$inv_id obj=".dump($obj, true));
  if(!$invObj) {
    $errors[] = "Invoice not found"; 
    $scope->error = $errors; 
    $scope->template = '403'; 
    return $scope;
  }
  $site_id = $siteObj->id;
  
  if($u_id) { // we're logged in 
    $user_id = $u_id;
    $auth_level = auth_invoice($invObj);
  } elseif($pin) { // check pin
    $scope->pin_code = $pin;
    $auth_level = myhash($invObj->booking_pin) == $pin ? USER_LEVEL_GUEST : 0;
    print_log("gh pin={$pin} auth:{$auth_level} id: {$invObj->id}", 'invoice', LOG_LEVEL_TEST);
    if(!$auth_level) $auth_level = myhash_old($invObj->booking_pin) == $pin ? USER_LEVEL_GUEST : 0; // grandfather clause
    if(!$auth_level) {
      $pin = '';
      $scope->error = "Invalid PIN";
      $scope->template = '403';
      return $scope;
    }
    //die("gh al=$auth_level");
  } else { // redirect to login
    $scope->redirect = page_link(PAGE_LOGIN)."?ref=".urlencode(this_path());
    return $scope;
  }

  print_log("ok pin={$pin} auth:{$auth_level} id: {$invObj->id}", 'invoice', LOG_LEVEL_TEST);

  $scope->auth_level = $auth_level;
  $scope->data = array_filter(array("obj_type" => 'invoice', "inv_id" => $inv_id, "pin"  => $pin)); // send to ajax fetch-template method and back to this controller (in options)
  
  if(!$auth_level) {
    $scope->error = "Unauthorized";
    $scope->template = '403';
    return $scope;
  }
  
  
  $scope->host_id = $host_id = $obj->host_id;
  $scope->is_host = $is_host = $u_id && $host_d && $u_id == $host_id;
  $scope->guest_id = $guest_id = $obj->guest_id;
  $scope->is_guest = $is_guest = $u_id && $guest_id && $u_id == $guest_id;
  $scope->auth_edit = $scope->auth_invoice = $auth_edit = $auth_level >= USER_LEVEL_STAFF; // can edit?
  $scope->show_contact = $auth_edit || $is_guest || $pin; 
  
  if($auth_edit) {
    $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.js";
    $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/locale/bootstrap-table-en-US.js"; /** todo: support other languages, use $_SESSION['locale']  */
    $__header['end_scripts'][] = "/afr/bower/bootstrap-table/dist/extensions/editable/bootstrap-table-editable.js";
    $__header['end_scripts'][] = "/afr/bower/x-editable/dist/bootstrap3-editable/js/bootstrap-editable.js";
    
    $__header['css'][] = "/afr/bower/bootstrap-table/dist/bootstrap-table.min.css";
    $scope->data_url = "/admin/app_data.php?oper=get-rows&obj_type=inv_lineitem&search=$inv_id"; //&return=rows";
    $scope->edit_url = "/admin/app_data.php?oper=edit&obj_type=inv_lineitem";
    $scope->title = "Edit invoice ".$invObj->invoice_number ?: $inv_id;
    
    
    $scope->inv_ids = $invObj->sequence ? find_objects('invoice', ['parent_type' => $invObj->parent_type, 'parent_id' => $invObj->parent_id], ['field' => 'invoice.id']) : [];
    $org_id = $invObj->org_id;
    $contact_id = $invObj->contact_id;
    $scope->contact = $contact_id ? get_object('contact', $contact_id) : null;
    $scope->contacts = $org_id ? find_objects('contact', ['org_id' => $org_id, 'active' => 1], ['sort' => 'organization, first_name']) : [];
    
  }

  $scope->public_link = $public_link = invoice_link($invObj);

  $parent_type = $invObj->parent_type;
  $parent_id = $invObj->parent_id;
  $guest_id = 0;
  $le_id = $invObj->legal_entity_id;
  $scope->legal_id = $le_id;
  $scope->reeleezee_username = $le_id ? get_object('legal_entity', $le_id, 'reeleezee_username') : '';
  
  $resObj = null;
  if($parent_type && $parent_id) {
    $parentObj = get_object($parent_type, $parent_id);
    if($parent_type == 'reservation') $resObj =  $parentObj;
    $scope->type_name = booking_type_name($resObj);     
  }
  $aptObj = $resObj = null;
  switch($parent_type) {
  case 'reservation':
    $scope->booking = $resObj = $parentObj;  
    $scope->due_now = $invObj->due_now = get_due_now($invObj, $resObj);   // how much is due now (either full amount or percentage of total
    //echo("Due = $due_now");
    $apt_id = $resObj->apt_id;
    $ptype = $resObj->property_type;
    $scope->rental = $aptObj = $apt_id && $ptype ? get_object($ptype, $apt_id) : null;
    $guest_id = $resObj->guest_id; 
    break;
  default:
    break;
  }
  $scope->invoice = $invObj;

  $scope->view = $template = pick_first($_GET['view'], $_GET['template'], $options['template'], "_invoice-overview.html");
  if($template && strpos($template, '_invoice-') === false) $template = $scope->view = "_invoice-{$template}.html"; // allow shortform
  switch($template) {
  case "_invoice-overview.html":
    if($auth_level >= USER_LEVEL_STAFF) {
      $scope->change_log = object_change_log($obj_type, $obj_id);
      $scope->mail_log = $mail_log = object_mail_log($obj_type, $obj_id);
    }
    
    
    break;
  case "_invoice-receive.html":
    $paymentTypes = array(PAYMENT_TYPE_CREDIT_CARD, PAYMENT_TYPE_CASH, PAYMENT_TYPE_BANK, PAYMENT_TYPE_PAYPAL, PAYMENT_TYPE_AGENT);
    $scope->payment_types = find_objects_assoc('payment_type', array('id' => $paymentTypes), array('first' => phrase('select', CAPITALIZE).'...'));
    $scope->payment_statuses = array(PAYMENT_STATUS_COMPLETED => 'Completed', PAYMENT_STATUS_PENDING => 'Pending');
    $scope->currencies = get_currencies();
    break;
  case "_invoice-export.html":
    break;
  case "_invoice-recalculate.html":
    $res_id = $invObj->res_id;
    $scope->content = html_h2("Was").print_invoice($invObj);
    recalculate_invoice($inv_id);
    $scope->content .= html_h2("Now").print_invoice($inv_id);
    break;
    
  case "_payment-overview.html":
  case "_invoice-payment.html":

    /** set up Mollie, PayPal */
    $live = $_SESSION['live'] || $_SESSION['live_payments_test'];
    $scope->paypal_key = $pp_key = get_config(($live ? "ppu" : "pput"), $siteObj->id);
    $scope->mollie_key = $mollie_key = get_config(($live ? "ml" : "mt"), $siteObj->id);
    $scope->mollie_methods = mollie_methods($mollie_key);    
    
    /** look for PayPal return */
    if($scope->txn_id = $_GET['tx']) {
      $scope->tx_st = $_GET['st'];
      $scope->tx_currency = $_GET['cc'];
      $scope->tx_amount = $_GET['amt'];
    }
    
    if($resObj && ($resObj->status == STATUS_RESERVED || $resObj->status == STATUS_COMPLETE) && $invObj->head_invoice && $invObj->type == INV_TYPE_BOOKING) { 
      $template = "mail/booking-mail";
      $guest_text = "this is a test";
      $mail_scope = ['receiver' => 'guest', 'profile_id' => $resObj->host_id, 'res_id' => $resObj->res_id, 'title' => "{$dear} {$guest_name},", 'personal_message' => $guest_text];
      $mail_template_options = [
        'scope' => $mail_scope, 
        'controller' => 'booking_status', 'replyto' => "noreply@{$siteObj->domain}"];
      //$body = smarty_mail_template($siteObj, $template, $mail_template_options);      
      
      $scope->mail_template = $template;    
      $scope->mail_controller = 'booking_status';    
      $scope->sender = $from;    
      $scope->receiver = $to;    
      $scope->subject = booking_mail_subject($resObj);    
      $scope->preview = $body;
    }
    
    /**
    $ccObjs = array();    
    if($u_id == $guest_id) { // user is paying
      $ccObjs = cc_user_cards($guest_id);  
    } elseif($auth_edit) { // owner, staff
      $ccObjs = cards_on_file(array('parent_type' => $parent_type, 'parent_id' => $parent_id));
    }
    if(count($ccObjs)) $scope->cards = cc_cards_printable($ccObjs);
    */
    break;
  case "_invoice-print.html":
    
    purge_invoices($inv_id);
    //dump($invObj);
    $scope->pdf_url = $pdf_url = create_pdf_invoice($invObj); // always create fresh PDF on view
    print_log("url of {$invObj->id}= {$pdf_url}", 'invoice', LOG_LEVEL_ALWAYS);
    break;
  case "_invoice-send.html":
    $invoice_id_required = get_object('legal_entity', $invObj->legal_entity_id, 'invoice_id_required') ? 1 : 0;
    if($invoice_id_required && !trim($invObj->invoice_id)) {
      $errors[] = "An Invoice ID is required before sending this invoice";
      if(1) {
        $export_link = html_link("?view=export", "export", ['class' => 'click-target', 'data-target' => '#invoice_export_link']);
        $errors[] = "Perhaps you need to $export_link the invoice first?";
      }
      $scope->error = $errors;
      return $scope;
    }

    $scope->mail_log = $mail_log = object_mail_log($obj_type, $obj_id);
    
    $pdf_url = create_pdf_invoice($invObj); // always create fresh PDF on view   

    $guest_text = phrase('you have a new invoice from %s (attached)', CAPS, $siteObj->name);
    $guest_name =  $invObj->guest_id ? get_user_name($invObj->guest_id) : get_name_string($invObj);
    $recipient = guest_email($invObj, true) ?: email_recipient($invObj->email_address, $guest_name);
    $guest_name = "People who pay";    
    
    $scope->mail_template = $template = "mail/mail-invoice";    
    $scope->mail_controller = $controller = "invoice";            
    
    $mail = new stdClass;
    
    $mail->sender = site_email($invObj->site_id, true) ?: site_email($siteObj);    
    $mail->recipient = $recipient;
    $mail->receiver_name = $guest_name;
    $mail->subject = mail_subject('invoice', $invObj);
    $mail->body = $body;
    $mail->main_message = phrase('you have a new invoice from %s (attached)', CAPS, $siteObj->name);
    $mail->personal_message = ""; 
    $mail->attachment = docroot().$pdf_url;
    $mail->obj_name = 'invoice';
    $mail->obj_type = 'invoice';
    $mail->obj_id = $invObj->id;
    $scope->mail  = $mail; 
    
    $site_name = str_replace(' ', '-', $siteObj->name);
    $invoice_id = $invObj->invoice_id ?: $invObj->id;
    $scope->attachment_name = str_replace(' ', '_', "$site_name invoice $invoice_id").'.pdf';
    break;
  default:
    break;
  }
  return $scope;
  
}

function controller_forgot_password($siteObj, $pageObj, $options = array()) {
  global $u_id;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $errors = array();
  
  if($guid = $_GET['guid']) {

    /** new: using phpauth */
    global $phpauth;
    $result = $phpauth->verifyKey($guid);
    if($result['error']) {
      $errors[] = $result['message'];
    } else {
      $prObj = new stdClass();
      $prObj->id = $result['id'];
      $prObj->user_id = $result['user_id'];
      $prObj->guid = $guid;
      $scope->reset = $prObj;
    }

    if($errors) {
      $scope->error= $errors;
      $scope->template = '403';      
      return $scope;
    }
    $scope->message = $messages;  
    $scope->template = "reset-password.html";
  }

  $scope->user_id = $u_id;
  return $scope;
}


function controller_user_account($siteObj, $pageObj, $options = array()) {
  global $u_id, $u_level, $__header;
  $__header['end_scripts'][] = "/afr/bower/iban/iban.js";
  
  //print_log("controller_user_account 1 u_id=$u_id", 'smarty', LOG_LEVEL_TEST);
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  if(!$u_id) {
    $scope->redirect = site_pagetype_link($siteObj, PAGE_LOGIN)."?ref=".site_pagetype_link($siteObj, PAGE_PROFILE);
    return $scope;
  }
  
  $obj = $_SESSION['this_object'];
  $obj_type = $scope->obj_type = $_SESSION['this_object_type'];
  $obj_id = $scope->obj_id = $_SESSION['this_object_id'];

  if($obj_type == 'user' && $obj_id && $obj) { // from slug
    $user_id = $obj_id;
    $userObj = $obj;
  } else {
    $user_id = $u_id;
    $userObj = $_SESSION['userObj'] ?: get_object('user', $user_id); // logged in user, already merged with profile
  }
  // for now
  // later (allow admins to edit other profiles): $scope->auth_edit = $auth_edit = auth_action('user', 'edit', $u_id);

  $scope->profile = $scope->user = $userObj;
  $scope->user_id = $userObj->id;
  $scope->auth_edit = $scope->auth_edit_account = $auth_edit = auth_user_account($user_id);
    
  if(!$auth_edit) {
    $scope->error = "Unauthorized";
    $scope->template = "404";
    return $scope;
  }
  
  $scope->view = $template = pick_first($_GET['view'], $_GET['template'], $options['template'], "_user-account-notifications.html");
  if($template && strpos($template, '_user-account-') === false) $template = $scope->view = "_user-account-{$template}.html"; // allow shortform

  // public
  switch($template) {
    case "_user-account-notifications.html":
      break;
    case "_user-account-security.html":
      break;
    case "_user-account-privacy.html":
      break;
    case "_user-account-password.html":
      break;
    /**
    case "_user-account-cards.html":
      $ccObjs = cc_user_cards($user_id);  
      $scope->cards = cc_cards_printable($ccObjs);      
      break;
      */
    case "_user-account-linking.html":
      $scope->link_requests = find_objects('user_map', ['host_user_id' => $user_id, 'verified' => 0]);
      $scope->linked_users  = find_objects('user_map', ['user_id' => $user_id]);
      $scope->auth_users    = find_objects('user_map', ['host_user_id' => $user_id, 'verified' => 1]);
      break;
    case "_user-account-payout.html":
      break;
    case "_user-account-transactions.html":
      $start = $scope->start = $_GET['start'] ?: 0;
      $limit = $scope->limit = 10;
      $scope->transactions = find_objects('payment', array("host_id" => $u_id));

      //$fields = array('res_id','created','status','city_id','city_name','checkin','checkout','apartment_name','currency','grand_total', 'chat_count');
      $fields = '';
      $searchOptions = array("fields" => $fields, "start" => $start, "limit" => $limit);
      $search = array("host_id" => $user_id, "status" => array(STATUS_COMPLETEED));
      $scope->transactions = find_objects("payment", $search, $searchOptions);
      $scope->transaction_count = count_objects("payment", $search);
      break;
    default:
      break;
  }
  //dump($scope);
  return $scope;  
}

/** new public: view user profile */
function controller_user_profile($siteObj, $pageObj, $options = array()) {
  global $u_id, $u_level, $__header;
  $__header['end_scripts'][] = "/afr/bower/lightslider/dist/js/lightslider.min.js";
  $__header['css'][] = "/afr/bower/lightslider/dist/css/lightslider.min.css";
  
  
  $global = $_SESSION['global_scope'];
  if($providers = $global->provider_keys) {
    foreach($providers as $provider_id) { 
      if(in_array($provider_id, $providers)) $scope->provider_profiles[$provider_id] =  find_object('provider_profile', array('site_id' => $siteObj->id, 'user_id' => $user_id, 'provider_id' => $provider_id));
    }
  }

  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  
  $obj = $_SESSION['this_object'];
  $obj_type = $scope->obj_type = $_SESSION['this_object_type'];
  $obj_id = $scope->obj_id = $_SESSION['this_object_id'];
  
  if($obj_type == 'user' && $obj_id && $obj) { // from slug
    $user_id = $obj_id;
    $userObj = $obj;
    if(!$userObj->active) {
      if($u_level < USER_LEVEL_STAFF) return controller_error("User not found", 404);
      $scope->message = "User not active";
    }
  } else {
    if(!$u_id) {
      $scope->error = "Missing User ID and not logged in";
      $scope->template = "404";
      return $scope;
    }
    $user_id = $u_id;
    $userObj = $_SESSION['userObj'] ?: get_object('user', $user_id); // logged in user, already merged with profile
  }
  // for now
  // later (allow admins to edit other profiles): $scope->auth_edit = $auth_edit = auth_action('user', 'edit', $u_id);

  $scope->profile = $scope->user = $userObj;
  $scope->user_id = $userObj->id;
 
  $scope->auth_edit = $auth_edit = $scope->auth_edit_user = auth_user_profile($user_id);
  
  $scope->auth_login = auth_login($user_id) && $u_id != $user_id;
  //die("al=".$scope->auth_login. " e=".$scope->auth_edit);
  
  /** property sites */
  if($ptype = $siteObj->property_type) {
    $scope->guest_reviews = find_objects("feedback", array("parent_type" => "reservation", "host_id" => $user_id, "published" => 1));
    $scope->host_reviews  = find_objects("feedback", array("parent_type" => "user", "parent_id" => $user_id, "published" => 1));
    $scope->host_listings = $host_listings = find_objects($ptype, array("host_id" => $user_id, "active" => 1), ["limit" => 25, "fields" => ['id', 'active', 'guid', 'type','name', 'media', 'address_city', 'address_country']]);
    //dump($host_listings);
    $scope->host_listings_count = count_objects($ptype, array("host_id" => $user_id, "active" => 1));
  }
  
  /** todo: art website or override */
  
  return $scope;
}

/** new: edit user profile */
function controller_edit_profile($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header, $u_level;
  
  $__header['end_scripts'][] = "/afr/bower/bootstrap-tags/dist/js/bootstrap-tags.min.js";
  $__header['css'][] = "/afr/bower/bootstrap-tags/dist/css/bootstrap-tags.css";

  $ptype = $siteObj->property_type ?: "";
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $scope->path = this_path();
  
  $obj = $_SESSION['this_object'];
  $obj_type = $scope->obj_type = $_SESSION['this_object_type'];
  $obj_id = $scope->obj_id = $_SESSION['this_object_id'];

  if($obj_type == 'user' && $obj_id && $obj) { // from slug
    $user_id = $obj_id;
    $userObj = get_user($obj_id);
  } else {
    $userObj = get_user($u_id); 
    $user_id = $u_id;
  }

  $scope->profile = $scope->user = $userObj;
  $scope->user_id = $userObj->id;
  $scope->auth_edit = $auth_edit = $scope->auth_edit_user = auth_user_profile($user_id);

  //die("edit $user_id = $auth_edit");

  if(!$auth_edit) {
    $scope->error = "Unauthorized $user_id";
    $scope->template = "404";
    return $scope;
  }
  
  $scope->view = $template = pick_first($_GET['view'], $_GET['template'], $options['template'], "_user-profile-overview.html");
  if($template && strpos($template, '_user-profile-') === false) $template = $scope->view = "_user-profile-{$template}.html"; // allow shortform
  
  if($provider_id = $_GET["provider_id"]) {
    $result = user_provider_profile($siteObj, $provider_id, $u_id);
    
    if($result->success) {
      $profileObj = $result->data;
      $scope->debug = dump($profileObj, true);
      $scope->view = $template = '_user-profile-verification.html';
    } else {
      $scope->error = $result->error;
      $scope->view = $template = '_user-profile-verification.html';
    }
  }

  $scope->uploader = user_profile_uploader($user_id, array("view" => "list", "handler" => "user_photo_handler")); // doesn't work in switch, as dependencies are not loaded      
  $scope->passport_uploader = user_profile_uploader($user_id, array("view" => "list", "field" => "passport", "resize" => 0)); // doesn't work in switch, as dependencies are not loaded      
  
  
  switch($template) {
    case "_user-profile-overview.html":
      break;
    case "_user-profile-settings.html":
      break;
    case "_user-profile-photos.html":
      break;
    case "_user-profile-message.html":
      $inbox_scope = controller_inbox($siteObj, $pageObj, $options);
      
      if($user_id == $u_id) {
        $scope->error = phrase('you cannot send a message to yourself', CAPITALIZE);
      }
      $scope->parent_type = $_GET['parent_type'];
      $scope->parent_id = $_GET['parent_id'];
      $scope->sender_id = $u_id;
      $scope->receiver_id = $user_id;
      $scope->form_redirect = $scope->thread_id = $thread_id = chat_thread_id((array) $scope);
      break;
    case "_user-profile-history.html":
      $fields = array('res_id','created','status','city_id','city_name','checkin','checkout','apartment_name','currency','grand_total', 'chat_count');
      $start = $scope->start = $_GET['start'] ?: 0;
      $limit = $scope->limit = 10;
      $search = array("guest_id" => $user_id, "status" => ['!=', STATUS_DRAFT]);
      $searchOptions = array("fields" => $fields, "start" => $start, "limit" => $limit);
      $trips = find_objects("reservation", $search, $searchOptions);
      foreach($trips as $k => $trip) {
        $trip->chat_count = count_objects('chat', ['parent_type' => "reservation", 'parent_id' => $trip->res_id]);;
        $trips[$k] = $trip;
      }
      
      $scope->trips = $trips;
      $scope->trip_count = count_objects("reservation", $search);
      break;
    case "_user-profile-bookings.html":
      $fields = array('res_id','created','status','city_id','city_name','checkin','checkout','apartment_name','currency','grand_total', 'chat_count');
      $start = $scope->start = $_GET['start'] ?: 0;
      $limit = $scope->limit = 10;
      $searchOptions = array("fields" => $fields, "start" => $start, "limit" => $limit);
      $search = array("host_id" => $user_id, "status" => array('<>', array(STATUS_DRAFT, STATUS_BLOCKED)));
      $scope->bookings = find_objects("reservation", $search, $searchOptions);
      $scope->booking_count = count_objects("reservation", $search);
      break;
    case "_user-profile-wishlist.html":
      $search = array("site_id" => $siteObj->id, "user_id" => $user_id);
      $wishlistObjs = find_objects("wishlist", $search) ?: array();
      foreach($wishlistObjs as &$wishlistObj) {
        $wishlistObj->obj = get_object($wishlistObj->obj_type, $wishlistObj->obj_id);
      }
      $scope->wishlist = $wishlistObjs;
      break;
    case "_user-profile-inbox.html":
      $inbox_scope = controller_inbox($siteObj, $pageObj, $options);
      $scope->threads = $inbox_scope->threads;
      $scope->inv_id = $inbox_scope->inv_id;
      break;
    case "_user-profile-verification.html":
      $global = $_SESSION['global_scope'];
      if($providers = $global->provider_keys) {
        foreach($providers as $provider_id) { 
          if(in_array($provider_id, $providers)) $scope->provider_profiles[$provider_id] =  find_object('provider_profile', array('site_id' => $siteObj->id, 'user_id' => $u_id, 'provider_id' => $provider_id));
        }
      }
      break;

    default:
      break;
  }

   //$scope->message = "u_id=$u_id user_id=$user_id auth=$auth_edit se={$scope->auth_edit} t2=$template";
   //$scope->auth_edit = 111;
   //$scope->auth_edit_user = 112;
   //return $scope;
   //die("gh3");

  //echo("o=$obj_id t=$template".dump($scope,true)); 
  return $scope;    
}

function controller_artist_profile($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];
  $__header['css'][] = '/afr/css/afr_gallery.css?ver='.$_SESSION['version'];

  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  //dump($scope);
  $obj_type = $scope->obj_type = $scope->obj_type ?: $_SESSION['this_object_type'];
  $obj_id = $scope->obj_id =  $scope->obj_id ?: $_SESSION['this_object_id'];
  $obj = $_SESSION['this_object'];
  
  if(!$obj_id) $obj_id = $u_id;
  
  //echo("ot=$obj_type id=$obj_id");
  //die('gh');
  if($obj_type == 'user' && $obj_id) { // from slug
    $user_id = $obj_id;
    $userObj = get_user($obj_id);
  } else {
    $userObj = $_SESSION['userObj']; // logged in user, already merged with profile
    $user_id = $u_id;
  }
  
  $scope->profile = $userObj;
  $scope->auth_edit = $auth_edit = auth_user_profile($user_id);
  $scope->auth_login = auth_login($user_id);
  
  $scope->auth_edit = $scope->auth_edit_user = $auth_edit; // scope auth_edit overrridden somewhere
  //die("AL=".$scope->auth_login." edit=".$auth_edit);

  // $al = auth_login($user_id);
  // echo("<br><br><br><br>user_id=$user_id u_id=$u_id auth_edit: $auth_edit al: $al");  
  // if($auth_edit) return controller_traveler_profile($siteObj, $pageObj, $options);
  
  $is_curator = $user_id && user_has_role($user_id, USER_ROLE_CURATOR);
  $is_artist = $user_id && user_has_role($user_id, USER_ROLE_ARTIST);

  // find curators  
  $scope->curator_ids = find_objects('media_collection_map', array('artist_id' => $user_id, 'curator_id' => array('>', 0)), array('fields' => 'distinct curator_id', 'debug_query' => 0));
  //dump($curator_ids);

  $url = $scope->url ?: this_url();
  if($is_curator) {
    $scope->template = "_user-profile-curator.html";
    $scope->curator_id = $curator_id = $user_id;
    $scope->curator_exhibitions = $curator_exhibitions = find_objects('media_collection', array('user_id' => $curator_id, 'type' => MEDIA_COLLECTION_TYPE_EXHIBITION, 'active' => 1));;
    $scope->curator_artworks = gallery_unique_artworks(array_find_key($curator_exhibitions, 'id'));
  } elseif($is_artist) {
    $scope->template = "_user-profile-artist.html";    

    $scope->artist_id = $artist_id = $user_id;
    $scope->artist_projects = $artist_projects = find_objects('media_collection', array('user_id' => $artist_id, 'type' => MEDIA_COLLECTION_TYPE_PROJECT, 'active' => 1));;
    if($project_ids = array_find_key($artist_projects, 'id')) {
      $scope->artist_artworks = gallery_unique_artworks($project_ids);          
      //$scope->artist_artworks = $artist_artworks = find_objects('media_collection_map', array('media_collection_id' => $project_ids, 'active' => 1));
    }
    $artist_exhibitions_ids = find_objects('media_collection_map', array('artist_id' => $artist_id, 'collection_type' => MEDIA_COLLECTION_TYPE_EXHIBITION, 'active' => 1), array('fields' => 'distinct media_collection_id'));
    $scope->artist_exhibitions = find_objects('media_collection', array('id' => $artist_exhibitions_ids, 'active' => 1));
  } else {
    $scope->template = "_user-profile-collector.html";
  }
  $display_name = $title = $userObj->display_name;
  
  $img_src = print_media($userObj->photo, array('source_only' => true, 'full' => true));
  /** Add facebook Open Graph tags */
  $__header['meta'][] = array('property' => 'og:image', 'content' => $img_src);
  $__header['meta'][] = array('property' => 'og:url', 'content' => $url);
  $__header['meta'][] = array('property' => 'og:title', 'content' => $display_name);
  $__header['meta'][] = array('property' => 'og:description', 'content' =>  strip_tags($userObj->description));    
  $__header['meta'][] = array('property' => 'article:author', 'content' =>  "https://www.facebook.com/vpatinabv");    

  $__header['link'][] = array('property' => 'image_src', 'content' =>  $img_src);    
  $__header['author'] = $display_name;    
  $__header['description'] = strip_tags($userObj->description);   
  $__header['title'] = $title;    
  
  return $scope;  
}                           


/** old - delete */
function controller_traveler_profile($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;

  $__header['end_scripts'][] = "/afr/bower/bootstrap-tags/dist/js/bootstrap-tags.min.js";
  $__header['css'][] = "/afr/bower/bootstrap-tags/dist/css/bootstrap-tags.css";

  $ptype = $siteObj->property_type ?: "shortstay";
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $scope->path = this_path();

  //$scope->request = $_GET ? dump($_GET, true) : dump($_POST, true);
  //$scope->stack = caller_stack();
  //$scope->options = dump($options, true);
  //$scope->page = dump($pageObj, true);
  
  $obj = $_SESSION['this_object'];
  $obj_type = $scope->obj_type = $_SESSION['this_object_type'];
  $obj_id = $scope->obj_id = $_SESSION['this_object_id'];

  if($obj_type == 'user' && $obj_id && $obj) { // from slug
    $user_id = $obj_id;
    $userObj = $obj;
    $userObj = user_merge_profile($userObj);
  } else {
    $userObj = $_SESSION['userObj']; // logged in user, already merged with profile
    $user_id = $u_id;
  }
  // for now
  // later (allow admins to edit other profiles): $scope->auth_edit = $auth_edit = auth_action('user', 'edit', $u_id);

  $scope->profile = $userObj;
  $scope->auth_edit = $auth_edit = $u_id == $user_id && !$obj_id;  /** last term to allow owner to view own public profile */

  if(!$auth_edit) {
    $scope->template = "_user-profile-public.html";
    $scope->guest_reviews = find_objects("feedback", array("parent_type" => "reservation", "host_id" => $user_id, "published" => 1));
    $scope->host_reviews  = find_objects("feedback", array("parent_type" => "user", "parent_id" => $user_id, "published" => 1));
    $scope->host_listings = find_objects($ptype, array("host_id" => $user_id, "active" => 1), ["limit" => 10]);
    $scope->host_listings_count = count_objects($ptype, array("host_id" => $user_id, "active" => 1));

    $global = $_SESSION['global_scope'];
    if($providers = $global->provider_keys) {
      foreach($providers as $provider_id) { 
        if(in_array($provider_id, $providers)) $scope->provider_profiles[$provider_id] =  find_object('provider_profile', array('site_id' => $siteObj->id, 'user_id' => $user_id, 'provider_id' => $provider_id));
      }
    }

    return $scope;
  }
  
  
  //$scope->debug = "u_id=$u_id user_id=$user_id auth=$auth_edit pt=$pageObj->page_type ot=$obj_type id=$obj_id name=$obj->username";
  
  $scope->view = $template = pick_first($_GET['view'], $_GET['template'], $options['template'], "_user-profile-overview.html");
  if($template && strpos($template, '_user-profile-') === false) $template = $scope->view = "_user-profile-{$template}.html"; // allow shortform

  // public
  switch($template) {
    case "_user-profile-settings.html":
      break;
    case "_user-profile-message.html":
      $inbox_scope = controller_inbox($siteObj, $pageObj, $options);
      if($user_id == $u_id) {
        $scope->error = phrase('you cannot send a message to yourself', CAPITALIZE);
      }
      $scope->parent_type = $_GET['parent_type'];
      $scope->parent_id = $_GET['parent_id'];
      $scope->sender_id = $u_id;
      $scope->receiver_id = $user_id;
      $scope->form_redirect = $scope->thread_id = $thread_id = chat_thread_id((array) $scope);
      break;

    default:
      break;
    
  }
  

  /** below only for authorized user */

                                     
  if($provider_id = $_GET["provider_id"]) {
    $result = user_provider_profile($siteObj, $provider_id, $u_id);
    
    if($result->success) {
      $profileObj = $result->data;
      $scope->debug = dump($profileObj, true);
      $scope->view = $template = '_user-profile-verification.html';
      //dump($profileObj);
    } else {
      $scope->error = $result->error;
      $scope->view = $template = '_user-profile-verification.html';
      //die("Error: ".dump($scope, true));
    }
  }

  //echo("tpl=$template");
  $scope->uploader = user_profile_uploader($user_id, array("view" => "list", "handler" => "user_photo_handler")); // doesn't work in switch, as dependencies are not loaded      
  $scope->passport_uploader = user_profile_uploader($user_id, array("view" => "list", "field" => "passport", "resize" => 0)); // doesn't work in switch, as dependencies are not loaded      
  
  switch($template) {
    case "_user-profile-overview.html":
      break;
    case "_user-profile-settings.html":
      break;
    case "_user-profile-photos.html":
      break;
    case "_user-profile-history.html":
      $fields = array('res_id','created','status','city_id','city_name','checkin','checkout','apartment_name','currency','grand_total', 'chat_count');
      $start = $scope->start = $_GET['start'] ?: 0;
      $limit = $scope->limit = 10;
      $search = array("guest_id" => $user_id, "status" => ['!=', STATUS_DRAFT]);
      $searchOptions = array("fields" => $fields, "start" => $start, "limit" => $limit);
      $trips = find_objects("reservation", $search, $searchOptions);
      foreach($trips as $k => $trip) {
        $trip->chat_count = count_objects('chat', ['parent_type' => "reservation", 'parent_id' => $trip->res_id]);;
        $trips[$k] = $trip;
      }
      
      $scope->trips = $trips;
      $scope->trip_count = count_objects("reservation", $search);
      break;
    case "_user-profile-bookings.html":
      $fields = array('res_id','created','status','city_id','city_name','checkin','checkout','apartment_name','currency','grand_total', 'chat_count');
      $start = $scope->start = $_GET['start'] ?: 0;
      $limit = $scope->limit = 10;
      $searchOptions = array("fields" => $fields, "start" => $start, "limit" => $limit);
      $search = array("host_id" => $user_id, "status" => array('<>', array(STATUS_DRAFT, STATUS_BLOCKED)));
      $scope->bookings = find_objects("reservation", $search, $searchOptions);
      $scope->booking_count = count_objects("reservation", $search);
      break;
    case "_user-profile-wishlist.html":
      $search = array("site_id" => $siteObj->id, "user_id" => $user_id);
      $wishlistObjs = find_objects("wishlist", $search) ?: array();
      foreach($wishlistObjs as &$wishlistObj) {
        $wishlistObj->obj = get_object($wishlistObj->obj_type, $wishlistObj->obj_id);
        //$wishlistObj->data = array_merge(
        //  array("obj_type" => $wishlistObj->obj_type, "obj_id" => $wishlistObj->obj_id), $search
        //);
      }
      $scope->wishlist = $wishlistObjs;
      //dump($wishlist);
      
      break;
    case "_user-profile-inbox.html":
      $inbox_scope = controller_inbox($siteObj, $pageObj, $options);
      $scope->threads = $inbox_scope->threads;
      $scope->inv_id = $inbox_scope->inv_id;
      break;
    case "_user-profile-verification.html":
      $global = $_SESSION['global_scope'];
      if($providers = $global->provider_keys) {
        foreach($providers as $provider_id) { 
          if(in_array($provider_id, $providers)) $scope->provider_profiles[$provider_id] =  find_object('provider_profile', array('site_id' => $siteObj->id, 'user_id' => $u_id, 'provider_id' => $provider_id));
        }
      }
      break;

    default:
      break;
  }
    
  return $scope;
}

function controller_inbox_item($siteObj, $pageObj, $options) {
   $scope->foo = "bar";
   return $scope;
}

/** only used for mail */
function controller_chat($siteObj, $pageObj, $options) {
  global $u_id;
  if(!$u_id) return $scope;
  $user_id = $u_id;  
  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $chat_id = pick_first($scope->chat_id, $option['chat_id'], $scope->obj_id, $option['obj_id']);
  $receiver_id = pick_first($scope->receiver_id, $option['receiver_id']); // to whom this mail is sent
  
  $scope->messages = [];
  if($chat_id) { /** todo: security */
    $chatObj = $scope->chat = get_object('chat', $chat_id);
    $sender_id = $chatObj->sender_id;
    $scope->sender = get_user($sender_id);
    $scope->parent_type = $parent_type = $chatObj->parent_type;
    $scope->parent_id   = $parent_id = $chatObj->parent_id;
    if($parent_type && $parent_id) {
      $parentObj = get_object($parent_type, $parent_id);
      
      switch($parent_type) {
      case 'reservation':
        $scope->booking = $parentObj;
        $scope->rental = get_object('property', $parentObj->apt_id);
        $scope->profile_id = $receiver_id == $parentObj->host_id ?  $parentObj->guest_id : $parentObj->host_id;
        
        break;
      default:
        break;
      }
    }
    
    $thread_id = $chatObj->thread;
    $scope->limit = $limit = 10;
    $scope->count = count_objects("chat", array("thread" => $thread_id));
    $chatObjs = find_objects("chat", array("thread" => $thread_id), array("sort" => "created DESC", "limit" => $limit));
    $scope->thread_id = $thread_id;
    $scope->thread = $chatObjs;
  }
  return $scope;
}

/** used for inbox page */
function controller_inbox($siteObj, $pageObj, $options) {
  global $u_id, $u_level;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  if(!$u_id) return $scope;
  $user_id = $u_id;  

  $thread_id = pick_first($scope->thread, $option['thread'], $_SESSION['slug']);

  if($thread_id) { // get one thread
    $user_ids = explode('-', $thread_id);
    if(count($user_ids) < 2 || ($u_level < USER_LEVEL_STAFF && !in_array($u_id, $user_ids))) {
      $scope->error = "Invalid thread";      
      return $scope;      
    }

    
    $chatObjs = find_objects("chat", array("thread" => $thread_id), array("sort" => "created DESC", "limit" => 0));

    
    if($scope->count = $count = count($chatObjs)) {
      $chatObj = $chatObjs[0]; // get first

      $scope->chat = $chatObj;
      
      $scope->parent_type = $parent_type = $chatObj->parent_type;
      $scope->parent_id   = $parent_id = $chatObj->parent_id;
            
      if($parent_type != 'reservation') { // look for any chat with reservation in this thread
        if($res_id = find_object("chat", array("thread" => $thread_id, "parent_type" => "reservation"), "parent_id")) {
          $scope->parent_type = $parent_type = 'reservation';
          $scope->parent_id   = $parent_id = $res_id;
        }
      }
          
      if($parent_type && $parent_id) $scope->parent = $parentObj = get_object($parent_type, $parent_id);
      
      switch($parent_type) {
      case 'reservation':
        $scope->booking = $resObj = $parentObj; // get_object("reservation", $parent_id);
        $scope->invoice = $invObj = booking_invoice($resObj);
        $scope->inv_id = $invObj->id;
        if($resObj->property_type && $resObj->apt_id) $scope->rental = get_object($resObj->property_type, $resObj->apt_id);
        break;
      case 'shortstay':
        $scope->rental = $parentObj; // get_object($parent_type, $parent_id);
        break;
      default:
        break;
      }
      
      // mark as read
      $unreadSearch = ["thread" => $thread_id, "read_on" => ATT_DEFAULT_NULL, "receiver_id" => $user_id];
      list($count, $errors) = update_objects("chat", ["read_on" => now()], $unreadSearch);
      
    }
    
    //$scope->this_sender_id = $user_ids[0];
    //$receiver_id = $user_ids[1];
    $scope->user_id1 = $user_ids[0];
    $scope->user_id2 = $user_ids[1];
    $scope->user_ids = $user_ids;
    
    if(in_array($u_id, $user_ids)) { // we're in this chat
      $scope->sender_id = $u_id;
      if($other_user_id = chat_thread_user($thread_id, $user_id)) { // get other user
        $scope->receiver_id = $other_user_id;
        $scope->other_user = get_user($other_user_id);
      }
    } else { // we're not in this chat (staff)
      $scope->sender_id = $sender_id = $user_ids[0];
      $scope->receiver_id = $receiver_id = isint($user_ids[1]) ? $user_ids[1] : 0;
      $scope->other_user = get_user($sender_id); 
      $scope->first_user = $receiver_id ? get_user($receiver_id) : null; 
    }
              
    $scope->thread_id = $thread_id;
    $scope->thread = $chatObjs;
    //die("count=$count".dump($scope,true));
    
  } else { // find all threads

    $chatFields = array("thread", "max(id) as id, thread, max(created) as created", 
                "max(distinct(parent_type)) as parent_type", "max(distinct(parent_id)) as parent_id",
                "count(*) as count");
    $chatOptions = array('group' => 'thread', 'fields' => $chatFields, 'sort' => 'created desc', "debug_query" => false);
    $chatSearch[DB_LOGICAL_OR] = array("sender_id" => $user_id, "receiver_id" => $user_id);    
    $scope->threads = $threads = find_objects("chat", $chatSearch, $chatOptions);
    foreach($threads as &$thread) {
      $thread->other_user_id = chat_thread_user($thread->thread, $user_id); // get other user
      
      $alertSearch = ["thread" => $thread->thread, "read_on" => ATT_DEFAULT_NULL, "receiver_id" => $user_id, "status_change" => [">", 0]];
      $unreadSearch = ["thread" => $thread->thread, "read_on" => ATT_DEFAULT_NULL, "receiver_id" => $user_id];
      
      $thread->alert = count_objects("chat", $alertSearch);
      $thread->unread_count = $unread = count_objects("chat", $unreadSearch);
    }
  }
  return $scope;
}



function controller_event($siteObj, $pageObj, $options = array()) {
  global $u_level, $auth_edit, $__header;
  $ver = $_SESSION['version'] ?: date('md');
  
  
  $__header['end_scripts'][] = "/afr/bower/ubilabs-geocomplete/jquery.geocomplete.min.js";
  $__header['end_scripts'][] = "/afr/js/afr_gmap.js";
  $__header['end_scripts'][] = "/afr/jquery/periodpicker/build/jquery.periodpicker.full.min.js";

  $__header['end_scripts'][] = "/afr/bower/bootstrap-confirmation2/bootstrap-confirmation.js";    
  $__header['end_scripts'][] = "/afr/js/event-form.js?v=$ver";    
  $__header['css'][] = "/afr/jquery/periodpicker/build/jquery.periodpicker.min.css";
  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $obj_type = 'event';
  
  $city = $options['city'] ?: 'Amsterdam';
  $country = $options['country'] ?: 'NL';
  $fields = array("id", "name", "notes", "start_address", "start_time", "end_time", "startdatetime", "enddatetime", "startdate", "enddate", "location_lat", "location_long","location_bounds","address_street","address_number","address_city","address_postcode","address_state","address_country","address_formatted");
  $id = pick_first($_GET['id'], $options['id'], $_GET['article_id'], $_SESSION['obj_id'], $_SESSION['slug'], $scope->event_id, $options['event_id']);

  $scope->auth_add_event = $u_level >= USER_LEVEL_EDITOR ? 1 : 0;
  
  if($id) {
    $scope->event = $obj = get_object($obj_type, $id);
    if($obj->user_level > $u_level) return controller_error("Not authorized", 401);
    $scope->id = $obj->id;
    if($media = $obj->media) $scope->media_list = explode(',', $media);
    $scope->uploader = object_media_uploader($obj_type, $id);
    $scope->auth_edit_event = $u_level >= USER_LEVEL_EDITOR || auth_event($obj);
    object_increment($obj_type, $id, 'views');
    
    return $scope;
  }

  // could return here if array not needed in single view
  // return $scope;
  
  // below only used if Javascript is disabled
  $where = $_GET['e'];  
  $eventSearch = array('site_id' => $siteObj->id, 'active' => 1, 'end_time' => ['>=', today()], 'user_level' => array('<=', $u_level));
  switch($where) {
  case 'l': // local
    $eventSearch['address_city'] = 'Amsterdam';
    break;
  case 'n': // local
    $eventSearch['address_country'] = 'NL';
    break;
  case 'i': // local
    $eventSearch['address_country'] = array('!=', 'NL');
    break;
  default:
    break;
  }
    
  if(is_array($search)) $eventSearch = array_merge($search, $eventSearch);
  $events = find_objects('event', $eventSearch, array('sort' => 'start_time'));
  foreach($events as &$event) { // assign classes for sorting
    if(strtolower($event->address_city) == strtolower($city)) $class = "local";    
    elseif(strtolower($event->address_country) == strtolower($country)) $class = "national";
    else $class = $event->address_country ? "international" : "";
    $event->loc_class = $class;
    $event->auth_edit_event = $u_level >= USER_LEVEL_EDITOR || auth_event($event);
  }
  
  
  $scope->events = $events;
  return $scope;  
}

function controller_blog($siteObj, $pageObj, $options = array()) {
  global $u_level;
  
  $options['object_subtype'] = ARTICLE_TYPE_BLOG;
  $blog_id = pick_first($_GET['blog_id'], $_SESSION['obj_id'], $_SESSION['slug'], $scope->blog_id, $options['blog_id']);
  $options['article_id'] = $blog_id;
  $scope = controller_article($siteObj, $pageObj, $options);
  
  $scope->auth_add_blog = $u_level >= USER_LEVEL_EDITOR ? 1 : 0;
  return $scope;  
}

function controller_news($siteObj, $pageObj, $options = array()) {
  global $u_level;
  
  $options['object_subtype'] = ARTICLE_TYPE_NEWS;
  $news_id = pick_first($_GET['news_id'], $_SESSION['obj_id'], $_SESSION['slug'], $scope->news_id, $options['news_id']);
  $options['article_id'] = $news_id;
  $scope = controller_article($siteObj, $pageObj, $options);
  
  $scope->auth_add_news = $u_level >= USER_LEVEL_EDITOR ? 1 : 0;
  return $scope;  
}

// generic controller for articles (news, blogs, etc). Requires that article type is set 

function controller_article($siteObj, $pageObj, $options = array()) {
  global $u_level, $auth_edit, $__LANG;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $obj_type = 'article';
  $fields = array("id", "type", "title", "content");

  $id = pick_first($_GET['id'], $options['id'], $_GET['article_id'], $_SESSION['obj_id'], $_SESSION['slug'], $scope->article_id, $options['article_id']);
  $scope->type = $type = pick_first($options['object_subtype'], $scope->object_subtype, $pageObj->object_subtype);

  $lang = $options['language'] ?: $__LANG;
  $user_level = $u_level ?: 0;
  $page_size = 5; // for pagination
  $hard_limit = 20;
  $limit = $options['limit'] ?: $hard_limit;
  $scope->auth_add_article = $auth_add = $u_level >= USER_LEVEL_EDITOR ? 1 : 0;
  
  $add = $scope->add = isset($_GET['add']) && $auth_add;
  
  if($id) {    
    $obj = get_object($obj_type, $id);
    $scope->article_id = $obj->id;
    $scope->auth_edit_article = $u_level >= USER_LEVEL_EDITOR || auth_article($obj);
    $scope->comments = find_objects('comment', array("article_id" => $id, 'active' => 1));
    if($auth_edit) {
      if(isset($_GET['publish'])) {
        $published = $_GET['publish'] ? 1 : 0;        
        if($published != $obj->published) {
          list($id, $errors) = update_object('article', ['published' => $published], $id);
          if($errors) return controller_error($errors);          
          $obj->published = $published;
        }
      }

      $scope->article->json_data = object_json_data($obj_type, $obj, $fields);
    
    } elseif(!$obj->published) {
      return controller_error("Not authorized");
    }
    
    $scope->edit = $edit = isset($_GET['edit']) && $auth_edit;
    if(!$edit) object_increment($obj_type, $id, 'views');
    $scope->article = $obj;
    
  } elseif($add) {
    // do nothing
  } elseif($type) {
    
    $start = 0;
    $search = ['site_id' => $siteObj->id, 'type' => $type, 'language' => $lang, 'active' => 1, 'published' => 1, 'user_level' => array('<=', $u_level ?: 0)];
    $searchOptions = ["sort" => "created DESC", "start" => $start, "limit" => $limit];
    $articles = find_objects($obj_type, $search, array('sort' => 'post_date desc'));  
    
    $sidebar_limit = 5;
    $scope->recent  = find_objects($obj_type, $search, array('sort' => 'created desc', 'limit' => $sidebar_limit));  
    $scope->popular = find_objects($obj_type, $search, array('sort' => 'views desc', 'limit' => $sidebar_limit));  
  
    if($auth_edit) {
      foreach($articles as &$article) {
        $article->json_data = object_json_data($obj_type, $article, $fields);
        $article->auth_edit_article = $u_level >= USER_LEVEL_EDITOR || auth_article($article);
      }
    }
    
    $scope->count = $count = count_objects('article', $search);
    //echo("Found $count articles");dump($search);
    $scope->articles = $articles;
    //dump($articles);
    
  } else {
    $scope->error = "No article ID or type set";
  }

  
  return $scope;
}

// todo: add limit, sort, paging
function controller_faq($siteObj, $pageObj, $options = array()) {
  global $__LANG;
  global $u_level, $auth_edit;
  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $obj_type = 'article';
  $facs = [];
  
  $search = ['site_id' => $siteObj->id, 'type' => ARTICLE_TYPE_FAQ, 'language' => $siteObj->default_language, 'active' => 1];
  $articleObjs = find_objects('article', $search, []);
  //dump($articleObjs);die("gh");
  foreach($articleObjs as $articleObj) {
    if($__LANG != $siteObj->default_language) {
      $descSearch = ['parent_type' => 'article', 'parent_id' => $articleObj->id];
      if($descObj = find_object('object_description', $descSearch)) {
        $articleObj->title = $descObj->title;
        $articleObj->content = $descObj->description;
        $desc_id = $descObj->id;
      } else {
        $descData = array_merge($descSearch, ['title' => $articleObj->title, 'description' => $articleObj->content, 'language' => $__LANG]);
        list($desc_id, $errors) = add_object('object_description', $descData);        
        //$articleObj->content = $descObj->content;
      }
      $articleObj->obj_type = 'object_description';    
      $articleObj->obj_id = $desc_id;    
      $articleObj->content_field = 'description';
    } else {
      $articleObj->obj_type = 'article';
      $articleObj->obj_id = $articleObj->id;    
      $articleObj->content_field = 'content';
    }
    $facs[] = $articleObj;
  }
  //dump($facs);
  $scope->articles = $facs;
  $scope->auth_edit_article = $u_level >= USER_LEVEL_STAFF;
  return $scope;
}



function controller_golf_club($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header, $__LANG;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $ver = $_SESSION['version'] ?: date('md');
  //$__header['scripts'][] = "/afr/bower/jquery-ui-map/ui/min/jquery.ui.map.full.min.js";
  //$__header['scripts'][] = "/afr/js/afr_gmap.js?v=$ver";
  $__header['css'][] = "/afr/css/afr-air.css";
  $obj_type = 'golf_club';
  $slug = $_SESSION['slug'];
  $id = $obj_id = $golf_club_id = $scope->obj_id = $scope->golf_club_id = pick_first($scope->golf_club_id, $scope->obj_id, $_GET['obj_id'], $options['obj_id'], $_SESSION['this_object_id']);
  
  if(!$id) { 
    $scope->error = $slug ? "$slug not found" : "No golf club specified";
    $scope->template = "403";
    return $scope;    
  }

  $obj = get_object($obj_type, $id);    
  
  
  if(!$obj) return scope_error("Golf club {$slug} not found", '404');
  $scope->golf_club = $obj;
  
  // $mediaObjs = object_images($obj_type, $id);
  $images = $obj->images ? json_decode($obj->images) : [];
  foreach($images as $mediaObj) {
    $image = new stdClass;
    $image->src = $mediaObj->filename;
    $image->title = $mediaObj->name;
    if($copyright = $mediaObj->copyright_name) {
      $copyright = html_i('', 'fa fa-copyright')." $copyright";
      $copyright_link = $mediaObj->copyright_url;
      $copyright_text = $copyright_link ? html_link($copyright_link, $copyright, array('target' => 'ext')) : $copyright;
      $image->copyright = html_div($copyright_text, 'copyright');        
    }
    $imageAr[] = $image;
  }
  

  $search = ['parent_type' => 'golf_club', 'parent_id' => $obj->id, 'language' => $__LANG];
  if($descObj = find_object('object_description', $search)) {
    $scope->description = $descObj;
  } elseif($descObj = find_object('object_description', ['parent_type' => 'golf_club', 'parent_id' => $obj->id])) { // any language
    $descData = ['language' => $__LANG];
    foreach(['site_id', 'parent_type', 'parent_id', 'type', 'description'] as $f) $descData[$f] = $descObj->$f;
    list($desc_id, $errors) = add_object('object_description', $descData);
    if($desc_id) $scope->description = get_object('object_description', $desc_id);
    if($errors) $scope->error = $errors;
  }
  
  $scope->golf_courses = $golf_courses = find_objects('golf_course', array('golf_club_id' => $id)) ?: array();
  //dump($golf_courses);
  
  //dump($imageAr);
  $scope->images = $imageAr;
  $scope->nearby_golf = location_find_nearest('golf_club', $obj->location_lat, $obj->location_long, array('limit' => 4, 'exclude' => $obj->id));
  $scope->nearby_apts = location_find_nearest('shortstay', $obj->location_lat, $obj->location_long, array('limit' => 4));      
  $scope->reviews = find_objects('feedback', array("parent_type" => $obj_type, "parent_id" => $id));

  $facAr = $obj->facilities ? explode(',', $obj->facilities) : array();
  $facs = array();
  foreach($facAr as $fac_id) {
    $facObj = new stdClass;
    $facObj->id = $fac_id;
    $facObj->name = get_object("facility", $fac_id, "name");
    $facObj->icon = rental_facility_icon($fac_id) ?: "fa fa-check";
    $facs[] = $facObj;
  }
  $scope->facs = $facs; // $scope->facilities = aptObj->facilities, already in use
  
  return $scope;
}

/** not in use 
function controller_preview($siteObj, $pageObj, $options = array()) {
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $parent_id = $scope->parent_id;
  $parent_type = $scope->parent_type;

  //if($parent_id && $parent_type) $scope->object = get_object($parent_type, $parent_id);
  $scope->obj_id = $parent_id;
  $scope->obj_type = $parent_type;
  
  $scope = controller_gallery_artworks($siteObj, $pageObj, ['scope' => $scope]);
  
  return $scope;
}
*/

/** mail preview function - for staff and higher only */
function controller_review($siteObj, $pageObj, $options = array()) {
  global $u_id, $u_level, $__header, $__CLIENT_ID, $__SITE;

  $obj = $_SESSION['this_object'];
  $obj_id = $scope->obj_id = $_SESSION['this_object_id'];
  

  $parent_type = pick_first($options['parent_type'], $_GET['_pt'], $siteObj->review_type);
  $parent_id = pick_first($options['parent_id'], $_GET['_pid']);
  $pin = $_GET['_pin'];

  if($obj) { /** View existing review */
    $scope->review = $obj;
    $parent_type = $obj->parent_type;
    $parent_id = $obj->parent_id;
    
  } elseif($parent_type) { /** add new review */
    $allow_multiple_reviews = 0;
    
    $scope->parent_type = $parent_type;
    if($parent_id) {
      $scope->parent_id = $parent_id;
      $scope->parent_object = $parentObj = get_object($parent_type, $parent_id);
      
      
      switch($parent_type) {          
        case 'reservation':
          $allow_multiple_reviews = 1;
          
          $resObj = $parentObj;
          if(!$resObj) return controller_error(phrase("booking not found", CAPS));
          
          $scope->reviewed_obj_type = $parent_type;
          $scope->reviewed_obj_id = $parent_id;
          $scope->reviewed_object = $parentObj;

          $scope->parent_id = $parent_id = $resObj->apt_id; /** we actually want to review the rental */ 
          $scope->parent_type = $parent_type = $resObj->property_type;
          $scope->parent_object = $parentObj = get_object($resObj->property_type, $resObj->apt_id);
          
          
          $today = today();
          $review_cutoff = BOOKING_REVIEW_PERIOD;
          $last_review_date = add_day(strip_time($resObj->checkout), $review_cutoff);
          if($u_id) {
            if($u_level < USER_LEVEL_STAFF && $resObj->guest_id && $u_id != $resObj->guest_id) return controller_error(phrase("only the guest can rate bookings", CAPS));
          } else {
            if($resObj->guest_id) redirect_login();
            if(myhash($resObj->booking_pin) != $pin) return controller_error(phrase("missing or invalid code", CAPS));           
          }
          if($reviewObj = find_object('review', ['reviewed_obj_type' => 'reservation', 'reviewed_obj_id' => $resObj->res_id])) {
            return controller_error(phrase("you already rated this %s on %s", CAPS, get_object_name('reservation'), sql2human($reviewObj->created)));
          }                              
          if(!in_array($resObj->status, [STATUS_RESERVED, STATUS_COMPLETE])) return controller_error(phrase("only confirmed bookings can be rated", CAPS));
          if($today > $last_review_date)  return controller_error(phrase("the review period expired on %s", CAPS, sql2human($last_review_date)));
          if(strip_time($resObj->checkout) > $today)  return controller_error(phrase("you cannot rate the booking until you check out on %s", CAPS, sql2human($resObj->checkout)));
          break;
        default:
          break;      
      }
    } 
  
    /** only allow user to review same item once ? Doesn't make sense for bookings, since they can stay in same flat twice... */
    if($u_id && !$allow_multiple_reviews) {
      if($reviewObj = find_object('review', ['user_id' => $u_id, 'parent_type' => $parent_type, 'parent_id' => $parent_id])) {
        return controller_error(phrase("you already rated this %s on %s", CAPS, get_object_name($parent_type), sql2human($reviewObj->created)));
        //$scope->review = $reviewObj;
      }
    }
  
  }
  
  $scope->items = $items = find_objects('review_item', ['site_id' => $siteObj->id, 'parent_type' => $parent_type]);
  if(!count($items)) return controller_error("No review items found for $parent_type");
    
  if(!$obj && !$parent_type) return controller_error("No review or parent");
  
  return $scope;
}

/** mail preview function - for staff and higher only */
function controller_mail_campaign($siteObj, $pageObj, $options = array()) {
  global $u_id, $u_level, $__header, $__CLIENT_ID, $__SITE, $__USER;
  global $__SITE_ROLES;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $campaign_id = pick_first($_GET['campaign_id'], $_SESSION['obj_id'], $_SESSION['slug'], $scope->campaign_id, $options['campaign_id']);

  $step = 0;
  if($campaign_id) {
    $scope->campaign = $campaignObj = get_object('mail_campaign', $campaign_id);
    $scope->campaign_id = $campaignObj->id;
    $step = isset($_GET['preview']) ? 3 : 2;
  }
  
  $scope->step = $step;
  
  $search = ['user.site_id' => $siteObj->id, 'active' => 1];
  
  $receiver_roles = $_GET['receiver_roles'];
  $selected_roles = $receiver_roles ? explode(',', $receiver_roles) : [];
  $selected_roles_str = [];
  
  if(!$step) {
    $receiver_count = $_GET['receiver_count'];
    $active_since = $_GET['active_since'];
    $name = trim($_GET['name']);  
    
    if($active_since) $search['last_login'] = ['>=', date2sql($active_since)];  
    $scope->users  = $users = find_objects('user', $search);
    $scope->user_count  = $count = count($users);
    
    $roleObjs = find_objects('user_role', [], ['sort' => 'id']);
    $roles = $role_terms = [];
    foreach($roleObjs as $roleObj) {
      if(is_array($__SITE_ROLES) && !in_array($roleObj->id, $__SITE_ROLES)) continue;
      $roleSearch = array_merge($search, ["roles & {$roleObj->id}" => $roleObj->id]);
      $users = find_objects('user', $roleSearch, ['debug_query' => 0]);
      $count = $roleObj->count = count($users);
      if($count || in_array($roleObj->id, $selected_roles)) $roles[] = $roleObj;
      if(in_array($roleObj->id, $selected_roles)) $selected_roles_str[] = $roleObj->name;
    }
    //echo("gh roles=".dump($roles,true));
    if($receiver_roles) {
      list($recipients, $errors) = campaign_recipients($_GET);
      if($errors) {
        $scope->error = $errors;
      } else {
        $scope->receiver_count = $receiver_count = count($recipients);
        $scope->message = "{$receiver_count} unique recipients found (some users have multiple roles)";
      }
      
      // dump($recipients);
      /**
      if(count($selected_roles) > 1) {
        foreach($selected_roles as $role_id) $role_terms["roles & {$role_id}"] = $role_id;
        $roleSearch = array_merge($search, [DB_LOGICAL_OR => $role_terms]);
      } else {
        $roleSearch = $search;
        $role_id = $selected_roles[0];
        $roleSearch["roles & {$role_id}"] = $role_id;
      }
      $scope->selected_users  = $selected_users = find_objects('user', $roleSearch);      
      $scope->receiver_count  = $receiver_count = count($selected_users);
      $active_str = $active_since ? "active since $active_since" : "";
      $roles_str = implode(',', $selected_roles_str);
      if($receiver_count) {
        $scope->message = "{$receiver_count} active users with roles $roles_str $active_str";
      } else {
        $scope->error = "No active users found with roles $roles_str $active_str";
      }
      */

      if($_GET['submit']) { // show step 2
        $campaign = array2obj($_GET);
        $campaign->sender = site_email($siteObj, $siteObj->name); 
        $campaign->subject = ""; // "[{$siteObj->shortname}]"; 
        $campaign->replyto = email_recipient(get_user_email($__USER),get_user_name($__USER));
        $campaign->recipients = json_encode($recipients); 
        $campaign->receiver_count = $receiver_count;
        if($active_since) $campaign->active_since = date2sql($active_since);
        
        // printable list of roles
        $roleObjs = find_objects('user_role', ['id' => $selected_roles]);
        $roles = [];
        foreach($roleObjs as $roleObj) $roles[] = $roleObj->name;

        $scope->receiver_roles_str = implode(", ", $roles);
        $scope->step = 2; // passed to template, not switch statement below
        $scope->receiver_count = $receiver_count;        
        $scope->campaign = $campaign;
      }
    }
    
    $scope->selected_roles = $selected_roles;
    $scope->roles = $roles;
    
  }
      
  return $scope;
}

/** contact form */
function controller_contact($siteObj, $pageObj, $options = array()) {
  global $__USER;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;

  $scope->replyto_sender = 1;
  
  print_log("controller_contact: scope=".dump($scope,true), 'mail', LOG_LEVEL_TEST);
  
  /** all of the below currently only used for vPatina plugin */
  
  if($sender = trim(urldecode($_GET['sender']))) {
    list($email, $name) = parse_recipient($sender);
    $scope->sender_name = $name;
    $scope->sender_email = $email;
    //echo("s=$sender n=$name e=$email"); 
  } elseif($__USER) {
    $scope->sender_name = $__USER->display_name;
    $scope->sender_email = $__USER->email_address;
    $scope->sender_phone = $__USER->phone;
  }
  if($recipient = trim(urldecode($_GET['recipient']))) {
    list($email, $name) = parse_recipient($recipient);
    $scope->receiver_name = $name;
    $scope->receiver_email = $email;
  }
  if($subject = trim(urldecode($_GET['subject']))) $scope->subject = $subject;

  if($msg = trim(urldecode($_GET['msg']))) $scope->main_message = $msg;
  else $scope->main_message = "You have a message from the contact form.";

  extract($_GET);
  
  $public = ['artwork', 'media_collection_map', 'collection'];
  if($obj_type && $obj_id && in_array($obj_type, $public)) {
    $template = '';
    $controller = '';
    if(!in_array($obj_type, $public)) return controller_error("Unsupported object type $obj_type");
    $obj = get_object($obj_type, $obj_id);
    if(!$obj) return controller_error("{$obj_type} {$obj_id} not found");
    
    switch($obj_type) {
    case 'media_collection_map':
    case 'artwork':
      $template = 'mail-artwork.html';
      $controller = 'gallery_artworks';
      break;
    case 'collection':
      $template = 'mail-collection.html';
      $controller = 'gallery_collections';
      break;
    default:
      return controller_error("Unsupported object type $obj_type");      
    }
    $scope->mail_template = $template;
    $scope->mail_controller = $controller;
    $scope->mail_obj_type = $obj_type;
    $scope->mail_obj_id = $obj_id;

    $scope->hide_title = 1;
    $scope->hide_phone = 1;
    $scope->hide_subject = 1;
  }
  

          
  return $scope;
}

/** mail preview function - for staff and higher only */
function controller_mail($siteObj, $pageObj, $options = array()) {
  global $u_id, $u_level, $__header, $__CLIENT_ID, $__SITE, $__USER;
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;

  $mid = pick_first($scope->obj_id, $scope->mail_id, $option['obj_id'], $scope->obj_id, $_GET['mid'], $_SESSION['this_object_id']);
  $uid = $_GET['uid'];

  $mailObj = null;
  if($mid) {
    $mailObj = get_object('mail_queue', $mid);
    $auth_mail = auth_mail($mailObj);
  } else if($uid) { // UID is almost impossible to guess, so no log-in/auth required other than correct client ID
    $mailObj = find_object('mail_queue', ['guid' => $uid]);
    $auth_mail = $mailObj->client_id == $__CLIENT_ID;
  }
  
  if($mailObj && !$auth_mail) {
    $scope->error = "Unauthorized $mid";
    return $scope;
  }
  
  $scope->auth_mail = $auth_mail;
  $scope->show_address_book = 0;
  
  if($mailObj) {
    $scope->mail = $mailObj;
   
  } elseif($u_id && $u_level >= USER_LEVEL_STAFF) { /** blank mail template */
    $scope->mail_template = $template = "mail/mail-generic";
    
    $sender_name = user_display_name($__USER->id);
    
    $guest_name =  $resObj->guest_id ? get_user_name($resObj->guest_id) : get_name_string($resObj);
    $mail_scope = ['receiver_name' => "", 
                   'receiver_role' => 'user', 
                   'receiver_id' => 0, 
                   'main_message' => phrase('you have a message from %s', CAPS, $sender_name)];
    
    $body = smarty_mail_template($siteObj, $template, ['scope' => $mail_scope]);
    
    $scope->mail_template = $template;    
    $scope->mail_action = '';            
    $scope->mail_scope = $mail_scope;            
    
    $mail = new stdClass;
    
    $mail->from = user_email($__USER, true) ?: site_email($siteObj);    
    $mail->to = "";    
    $mail->subject = mail_subject('mail');
    $mail->body = $body; 
    $scope->mail  = $mail;
    
    $scope->show_address_book = $u_id ? 1 : 0;
    
  } elseif($u_id) {
    return controller_error(phrase("nothing to see here", CAPS));    
  } else {
    return controller_error(phrase("please log in", CAPS));    
  }
     
  return $scope;
}

function controller_share($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];
  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;

  extract($_GET);
  print_log("share ctrl get=".dump($_GET,true), 'gallery', LOG_LEVEL_TEST);
  if($data_json = $_GET['data']) {    
    $data = json_decode($data_json, true);
    $title = $data['title'];
  }
  
  $user_email = $from = $user_name = '';
  if($user_id = $data['uid'] ?: $u_id) {
    $user_email = get_user_email($u_id);
    $user_name = user_display_name($u_id);
    $from = $user_email ? email_string($user_email, $user_name) : '';
  }
  
  if(!$subject) {
    if($user_name) $subject = "$user_name shared this with you from $siteObj->name";
    else $subject = "Shared with you from $siteObj->name";
    if($title) $subject .= ": $title";
  }
  $preview = '';
  if($template = $_GET['template']) {                  
    $pObj = new stdClass;
    $pObj->template = $template;             
    $pObj->controller = $controller = $_GET['controller']; 
    //$data = ['foo1' => 'bar2'];                       
    $data['url'] = $url;
    $preview = fetch_template($siteObj, $pObj, array('scope' => $data));
    print_log("preview $template/$controller  len=".strlen($preview), 'gallery', LOG_LEVEL_TEST);    
  }
  
  $scope->user_id = $u_id;
  $scope->from_name = $user_name;
  $scope->from_email = $user_email;

  $scope->from = $from;
  $scope->subject = $subject;
  $scope->vars = $_GET;
  $scope->preview = str_replace($preview, '"', '\"');
  $scope->html_stripped = true; // strip header and footer 
  return $scope;
}

/** vPatina + Art controllers */
/** using old code: todo: replace with new controllers and templates */
     

function controller_gallery_artists($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $__header['css'][] = '/afr/css/afr_gallery.css?ver='.$_SESSION['version'];
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $scope->items = $scope->objects;  
  // unset($scope->objects);

  if($obj_id = $artist_id = $scope->obj_id = $_SESSION['this_object_id']) {
    return  controller_artist_profile($siteObj, $pageObj, $options);

  } else { /** browse artists: todo */
    $myCollectionObj = gallery_find_user_collection($siteObj, $u_id);
    $scope->my_collection_id = $collection_id = $myCollectionObj->id;
    $scope->items = $scope->objects ?: gallery_collection_images($siteObj, $collection_id, array('return' => 'object'));
    // unset($scope->objects);
  }

  return $scope;
}

function controller_gallery_curators($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $__header['css'][] = '/afr/css/afr_gallery.css?ver='.$_SESSION['version'];
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];
  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $scope->items = $scope->objects;

  if($obj_id = $artist_id = $scope->obj_id = $_SESSION['this_object_id']) {
    return  controller_artist_profile($siteObj, $pageObj, $options);

  } else { /** browse curators: todo */
    $myCollectionObj = gallery_find_user_collection($siteObj, $u_id);
    $scope->my_collection_id = $collection_id = $myCollectionObj->id;
    $scope->items = $scope->objects ?: gallery_collection_images($siteObj, $collection_id, array('return' => 'object'));
    // unset($scope->objects);
  }
  
  return $scope;
}


// my-vpatina (view, explore art)
function controller_art_viewer($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];
  $__header['css'][] = '/afr/css/afr_gallery.css?ver='.$_SESSION['version'];
  
  //dump($__header);
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $aif = $_GET['_aif'];
  $scope->my_collection_id = $collection_id = gallery_find_user_collection($siteObj, $u_id, array('return' => 'id'));    

  /** follow media from GET var (plugin) */
  if(isint($aif)) {
    if(!$collection_id) {$scope->error = "Missing user collection"; return $scope;}
    $mediaObj = get_object('media', $aif);
    if(!$mediaObj) {$scope->error = "Artwork not found"; return $scope;}
    $media_name = $mediaObj->name ?: "this artwork";
    if($mapObj = find_object('media_collection_map', array('media_id' => $aif, 'media_collection_id' => $collection_id))) {
      $scope->warning = "You already follow $media_name";
    } else {
      $result = gallery_publish_image($siteObj, $aif, $collection_id);
      if($result->success) {
        $scope->message = "You now follow $media_name";
      } else {
        $scope->error = $result->error;
      }
    }
    $scope->follow_id = $aif; 
  }
  
  //dump($myCollectionObj);
  
  return $scope;
}  

// my-vault (CMS)           
function controller_art_explorer($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $ver = $_SESSION['version'];

  
  $__header['css'][] = '/afr/css/afr_gallery.css?ver='.$_SESSION['version'];
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];
  $__header['scripts'][] = '/afr/bower/jquery-zclip/jquery.zclip.js';
  $__header['scripts'][] = '/afr/bower/jquery-validate/dist/jquery.validate.min.js';
  if($_SESSION['lang'] != 'en') $__header['scripts'][] = '/afr/bower/jquery-validate/localization/messages_'.$_SESSION['lang'].'.js';
  $__header['scripts'][] = "/afr/js/afr_cms.js?v=$ver";
  $__header['scripts'][] = "/afr/js/afr_cms_dynatree.js?v=$ver";
  $__header['scripts'][] = '/afr/bower/dynatree/dist/jquery.dynatree.min.js';
  $__header['css'][] = '/afr/css/afr_gmenu.css';
  $__header['css'][] = '/afr/bower/dynatree/dist/skin/ui.dynatree.css';

  //$__header['css'][] = '/afr/jquery/fancybox/vp.css'; // for preview

  jfu_dependencies('bootstrap'); // load scripts + css for new file uploader

  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;

  $scope->create_button = gallery_create_button($siteObj, $u_id);  
  $scope->vault = 1;  
  //$scope->explorer = site_page_edit_gallery($siteObj, $pageObj, $options);
  return $scope;
}


function controller_gallery_artworks($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $__header['css'][] = '/afr/css/afr_gallery.css?ver='.$_SESSION['version'];
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];
  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $obj_id = $scope->obj_id = $scope->obj_id ?: $_SESSION['this_object_id'];
  $obj_type = $scope->obj_type= $scope->obj_type ?: "media_collection_map"; // $_SESSION['this_object_type'];
  
  $parent_obj_type = $scope->parent_obj_type;
  $parent_obj_id = $scope->parent_obj_id;
  
  print_log("controller_gallery_artworks: $obj_type/$obj_id parent: $parent_obj_type/$parent_obj_id", 'gallery', LOG_LEVEL_TEST);
  // When coming from plug-in, we don't have map id. Find it
  if($obj_type == 'media' && $obj_id && $parent_obj_type == 'media_collection' && $parent_obj_id) {
    if($mapObj = find_object('media_collection_map', ['media_collection_id' => $parent_obj_id, 'media_id' => $obj_id])) {
      print_log("controller_gallery_artworks: found map:".dump($mapObj, true), 'gallery', LOG_LEVEL_TEST);
      $obj_id = $scope->obj_id = $mapObj->id;
      $obj_type = $scope->obj_type = 'media_collection_map';      
    }
  }
  
  $scope->my_collection_id = $scope->user_collection_id = $user_collection_id = $u_id ? gallery_find_user_collection($siteObj, $u_id, array('return' => 'id')) : 0;
  $scope->follow_type = "media";
    
  if($obj_id) {
    $obj = get_object($obj_type, $obj_id); 
    
    $scope->obj_id = $obj_id;
    
    switch($obj_type) {
    case 'media':
      $scope->artwork = $mediaObj = get_object('media', $obj_id);
      $scope->artist_id = $artist_id = $mediaObj->artist_id ?: $mediaObj->user_id;
      $scope->media_id = $media_id = $scope->artwork->media_id = $obj_id;
      $scope->email_template = 'mail/mail-sharing-artwork.html';
      
      break;
    case 'media_collection_map':
      
      $scope->artwork = $artworkObj = get_artwork($obj_id);
      $scope->artist_id = $artist_id = $artworkObj->artist_id;
      $scope->media_id = $media_id = $scope->artwork->media_id = $artworkObj->media_id; 
      $scope->email_template = 'mail/mail-sharing-artwork.html';
      
      $related = gallery_artwork_related($siteObj, $obj);
      foreach($related as $k => $v) $scope->$k = $v;

      if($curator_id = $related->curator_id) {
        $scope->curator_exhibitions = $curator_exhibitions = find_objects('media_collection', array('user_id' => $curator_id, 'type' => MEDIA_COLLECTION_TYPE_EXHIBITION, 'active' => 1));;
        $scope->curator_artworks = gallery_unique_artworks(array_find_key($curator_exhibitions, 'id'));
      }
      if($artist_id) {
        $scope->artist_name = $artist_name = user_display_name($artist_id);
        $scope->artist_projects = $artist_projects = find_objects('media_collection', array('user_id' => $artist_id, 'type' => MEDIA_COLLECTION_TYPE_PROJECT, 'active' => 1));;
        //$scope->artist_exhibitions = $artist_exhibitions = find_objects('media_collection', array('user_id' => $curator_id, 'type' => MEDIA_COLLECTION_TYPE_EXHIBITION, 'active' => 1));;

        if($project_ids = array_find_key($artist_projects, 'id')) {
          $scope->artist_artworks = gallery_unique_artworks($project_ids);          
          //$scope->artist_artworks = $artist_artworks = find_objects('media_collection_map', array('media_collection_id' => $project_ids, 'active' => 1));
        }
        
        $artist_exhibitions_ids = find_objects('media_collection_map', array('artist_id' => $artist_id, 'collection_type' => MEDIA_COLLECTION_TYPE_EXHIBITION, 'active' => 1), array('fields' => 'distinct media_collection_id'));
        $scope->artist_exhibitions = find_objects('media_collection', array('id' => $artist_exhibitions_ids, 'active' => 1));
      }
      break;
    default:
      $scope->error = "Illegal type $obj_type";
      $scope->template = "404";
      break;
    }
    
    $artwork = $scope->artwork;
    $title = $artwork->name ?: "Untitled";
    $title .= " by $artist_name";
    $description = implode('. ', array_filter(array($artwork->original_technique, $artwork->short_description, $artwork->comment)));
    $scope->follow_id = $artwork->media_id;

    if($u_id && isset($_GET['follow']) && $user_collection_id && $media_id) { /** follow this artwork */
      $follow = $_GET['follow'] ? 1 : 0;
      if($mapObj = find_object('media_collection_map', array('media_id' => $media_id, 'media_collection_id' => $user_collection_id))) {
        if(!$follow) delete_object('media_collection_map', $mapObj->id);
        /** do nothing, already following */
      } else {
        if($follow) $result = gallery_publish_image($siteObj, $media_id, $user_collection_id);
      }    
    }
    
    $img_src = print_media($artwork->media_id, array('source_only' => true, 'full' => true));
    /** Add facebook Open Graph tags */
    $__header['meta'][] = array('property' => 'og:image', 'content' => $img_src);
    $__header['meta'][] = array('property' => 'og:url', 'content' => $scope->url ?: this_url());
    $__header['meta'][] = array('property' => 'og:title', 'content' => $title);
    $__header['meta'][] = array('property' => 'og:description', 'content' =>  strip_tags($description));    
    //$__header['meta'][] = array('property' => 'article:author', 'content' =>  "Some Dude");    
    $__header['meta'][] = array('property' => 'article:author', 'content' =>  "https://www.facebook.com/vpatinabv");    

    $__header['link'][] = array('property' => 'image_src', 'content' =>  $img_src);    
    $__header['author'] = $artist_name;    
    $__header['description'] = strip_tags($description);   
    $__header['title'] = $title;    
    
    /** check if this artwork is in user's collection */
    $scope->collected = $scope->my_collection_id = 0;
    $media_id = $scope->artwork->media_id;    
    if($u_id && $media_id) {
      $scope->collected = $collected = find_object('media_collection_map', array('media_collection_id' => $user_collection_id, 'active' => 1, 'media_id' => $media_id), array('fields' => 'id')) ? 1 : 0;
    }
    
    $scope->artist = $artistObj = $artist_id ? get_user($artist_id) : null;
  } elseif($objects = $scope->objects) { /** from app_data?oper=gallery-get-collection */
    $scope->items = $scope->objects;
    
    /** all collected images */
    $scope->user_collection = $user_collection_id ? find_objects('media_collection_map', array('media_collection_id' => $user_collection_id, 'active' => 1), array('fields' => 'distinct (media_id)', 'sort' => 'id DESC')) : array();      
    
  } else { /** browse artworks: todo */
  }
                                 
  return $scope;
}
                               
function controller_plugin($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $__header['css'][] = '/afr/css/afr_gallery.css?ver='.$_SESSION['version'];
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];

  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $obj_id = $media_id = $scope->obj_id ?: $_SESSION['this_object_id'];
  $obj_type = $scope->obj_type ?: "plugin";
  if($obj_type != 'plugin') return controller_error("Missing ID or Illegal type $obj_type");

  if($obj_id) {
    $obj = $plugin =$scope->plugin = get_object($obj_type, $obj_id);
    if(!$obj) return controller_error("Could not find $obj_type $obj_id");
  }

  if($obj) {
    $parent_type = $plugin->parent_type;
    $parent_id = $plugin->parent_id;
  } else {
    $parent_type = pick_first($_GET['pt'], $scope->parent_type, $options['parent_type']);
    $parent_id = pick_first($_GET['pid'], $scope->parent_id, $options['parent_id']);
  }
  
  if($parent_type && $parent_id) {
    $scope->parent_object = $parent_object = get_object($parent_type, $parent_id);
    if(!$parent_object) return controller_error("Could not find $parent_type $parent_id");

    $scope->parent_type = $parent_type;
    $scope->parent_id = $parent_id;
    
    $scope->plugins = $plugins = find_objects('plugin', array('parent_id' => $parent_id, 'parent_type' => $parent_type));
    $scope->plugin_count = count($plugins);

    
    if($parent_type == 'media_collection') {
      $scope->collection = $parent_object;
      $scope->preview = plugin_javascript(['shid' => $plugin->id]);
      $scope->preview_html = sharing_output(['shid' => $plugin->id]);

      $scope->images = $images = find_objects('media_collection_map', ['media_collection_id' => $parent_id, 'active' => 1], ['sort' => 'rank']);
    }
  }
  
  return $scope;
  
  /** old code */
  
  $scope->foo = 'bar';
  $auth_edit = $scope->auth_edit = gallery_auth_media($obj_type, $obj, $u_id);
  
  if($auth_edit && $obj_type == 'media_collection') {
    if($sharing_id = $scope->sharing_id) { // edit single
      $scope->sharing = get_object('sharing', $sharing_id);
      if($scope->preview) {
        $scope->sharing_preview = sharing_output(array('shid' => $sharing_id), array('preview' => 1));
      }
    } else { // add
      $scope->sharing = $sharing =  find_objects('sharing', array('parent_id' => $obj_id, 'parent_type' => $obj_type));
      $scope->sharing_count = count($sharing);
    }
  }
  
  if($auth_edit && $obj_type == 'media_collection') {
    if($sharing_id = $scope->sharing_id) { // edit single
      $scope->sharing = get_object('sharing', $sharing_id);
      if($scope->preview) {
        $scope->sharing_preview = sharing_output(array('shid' => $sharing_id), array('preview' => 1));
      }
    } else { // add
      $scope->sharing = $sharing =  find_objects('sharing', array('parent_id' => $obj_id, 'parent_type' => $obj_type));
      $scope->sharing_count = count($sharing);
    }
  }

}


function controller_gallery_folder($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $__header['css'][] = '/afr/css/afr_gallery.css?ver='.$_SESSION['version'];
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];
  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $obj_id = $media_id = $scope->obj_id ?: $_SESSION['this_object_id'];
  $obj_type = $scope->obj_type ?: "gallery";

  if(!$obj_id || $obj_type != 'gallery') {
    $scope->error = "Missing ID or Illegal type $obj_type";
    $scope->template = "404";
  }

  $obj = get_object($obj_type, $obj_id); 
  if(!$obj) {
    $scope->error = "Could not find $obj_type $obj_id";
    $scope->template = "404";
  }
  $auth_edit = $scope->auth_edit = gallery_auth_media($obj_type, $obj, $u_id); 
  
  $scope->artist_id = $artist_id = $obj->user_id;
  $scope->artist_name = $artist_name = user_display_name($artist_id);
  $scope->artist = $artistObj = $artist_id ? get_user($artist_id) : null;
  $scope->obj_id = $scope->folder_id = $obj_id;
  $scope->folder = $obj;
  $scope->artworks = find_objects('media', array('parent_type' => $obj_type, 'parent_id' => $obj_id, 'active' => 1));
  
  return $scope;
}

function controller_gallery_collections($siteObj, $pageObj, $options = array()) {
  global $u_id, $__header;
  $__header['css'][] = '/afr/css/afr_gallery.css?ver='.$_SESSION['version'];
  $__header['scripts'][] = '/afr/js/afr_gallery.js?ver='.$_SESSION['version'];
  

  
  $scope = $options['scope'] ? array2obj($options['scope']) : new stdClass;
  $scope->items = $scope->objects;  
  // unset($scope->objects);
  $obj_id = $media_id = $scope->obj_id = $scope->obj_id ?: $_SESSION['this_object_id'];
  $obj_type = $scope->obj_type = $scope->obj_type ?: $_SESSION['this_object_type'];
  
  print_log("sot: {$scope->obj_type} tos {$_SESSION['this_object_type']} => {$obj_type}", 'gallery', LOG_LEVEL_TEST);
  $scope->my_collection_id = $scope->user_collection_id = $user_collection_id = $u_id ? gallery_find_user_collection($siteObj, $u_id, array('return' => 'id')) : 0;
  $scope->follow_type = $obj_type;
  if($obj_id) {
    $scope->follow_id = $obj_id;
    $scope->user_collection = $user_collection_id ? find_objects('media_collection_map', array('media_collection_id' => $user_collection_id, 'active' => 1), array('fields' => 'distinct (media_id)')) : array();
    $scope->collection_id = $scope->obj_id = $collection_id = $obj_id;
    $scope->collection = $collectionObj = get_object('media_collection', $obj_id);
    $scope->email_template = 'mail/mail-sharing-collection.html';

    /** find artwork in collection */
    $scope->artworks = $artworks = find_objects('media_collection_map', array('media_collection_id' => $collection_id, 'active' => 1), array('sort' => 'rank'));

    if($collectionObj->type == MEDIA_COLLECTION_TYPE_EXHIBITION) {
      if($scope->curator_id = $curator_id = $collectionObj->user_id) $scope->curator = get_user($collectionObj->user_id);
      $scope->curator_exhibitions = $curator_exhibitions = find_objects('media_collection', array('id' => array('!=', $collection_id), 'user_id' => $curator_id, 'type' => MEDIA_COLLECTION_TYPE_EXHIBITION, 'active' => 1));;
      $scope->curator_artworks = gallery_unique_artworks(array_find_key($curator_exhibitions, 'id'));
    }

    $scope->url = site_full_url($siteObj).page_link(PAGE_GALLERY, 'media_collection', $collectionObj->type).slugify($collectionObj->title)."~".$obj_id;  

    $curator_id = $collectionObj->user_id;
    
    $mid = isset($_GET['mid']) ? $_GET['mid'] : 0;
    if($mid) {
      $artwork = get_object('media', $mid);
      $author_name = user_display_name($artwork->artist_id);
      $title = $artwork->name ?: "Untitled Artwork";
      $title .= " by $author_name";
      $description = implode('. ', array_filter(array($artwork->original_technique, $artwork->short_description, $artwork->comment)));

    } else {
      $author_name = user_display_name($curator_id);
      $title = $collectionObj->title ?: "Untitled Exhibition";
      $title .= " by $author_name";
      $description = $collectionObj->description;
    }

    if($loc_id = $collectionObj->location_id) {
      $locObj = get_object('location', $loc_id);
      $scope->collection->location = $locObj;
    }

    if($event_id = $collectionObj->event_id) {
      $eventObj = get_object('event', $event_id);
      $scope->collection->event = $eventObj;
    }
    
    $img_src = $mid ? print_media($mid, array('source_only' => true, 'full' => true)) : collection_title_image($collectionObj);
  
    /** Add facebook Open Graph tags */
    $__header['meta'][] = array('property' => 'og:image', 'content' => $img_src);
    $__header['meta'][] = array('property' => 'og:url', 'content' => $scope->url ?: this_url());
    $__header['meta'][] = array('property' => 'og:title', 'content' => $title);
    $__header['meta'][] = array('property' => 'og:description', 'content' =>  strip_tags($description));    
    //$__header['meta'][] = array('property' => 'article:author', 'content' =>  "Some Dude");    
    $__header['meta'][] = array('property' => 'article:author', 'content' =>  "https://www.facebook.com/vpatinabv");    
  
    $__header['link'][] = array('property' => 'image_src', 'content' =>  $img_src);    
    $__header['author'] = $author_name;    
    $__header['description'] = strip_tags($description);
    $__header['title'] = $title;    
    
  } else { /** find collections */
    //$scope->error = "got here type=$type artist_id=$artist_id".dump($options, true);
    //return $scope;
    
    if($items = $scope->items) { // my-vpatina
      //$myCollectionObj = gallery_find_user_collection($siteObj, $u_id);
      //$scope->my_collection_id = $collection_id = $myCollectionObj->id;
      //$scope->items = $scope->objects ?: gallery_collection_images($siteObj, $collection_id, array('return' => 'object'));
      //$scope->error = "got here id=$obj_id count=".count($items);
    } else { // my-vault
      $collection_type = $scope->type ?: MEDIA_COLLECTION_TYPE_EXHIBITION;
      if(!$collection_type) {
        $scope->error = "Missing collection type";
        $scope->template = "404";
        return $scope;    
      }
      $search = array('type' => $collection_type, 'active' => 1);
      $user_id = pick_first($scope->artist_id, $scope->user_id, $u_id);    
      $search['user_id'] = $user_id;
      $scope->items = $items = find_objects('media_collection', $search);
      $scope->vault = 1;
    }
    
  }

  $scope->auth_edit = $auth_edit = $obj_type && $obj_id ? gallery_auth_media($obj_type, $obj_id, $u_id) : false; 
 //  update location set location_bounds ='[["36.6504","-6.1641"],["36.6684","-6.1461"]]' where id=8746;
  if($auth_edit && $obj_type == 'media_collection') {
    if($sharing_id = $scope->sharing_id) { // edit single
      $scope->sharing = get_object('sharing', $sharing_id);
      if($scope->preview) {
        $scope->sharing_preview = sharing_output(array('shid' => $sharing_id), array('preview' => 1));
      }
    } else { // add
      $scope->sharing = $sharing =  find_objects('sharing', array('parent_id' => $obj_id, 'parent_type' => $obj_type));
      $scope->sharing_count = count($sharing);
    }
  }
  
  print_log("eot: {$scope->obj_type}", 'gallery', LOG_LEVEL_TEST);
  
  // unset($scope->objects);
  return $scope;
}

/** End vPatina + Art controllers */
