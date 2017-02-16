<?php


/** geocode galleries 
    todo: make automatic 
*/
function geocode_galleries() {  
  $userObjs = find_objects('user', ["user.site_id" => 247, "user_level" => 26]);
  foreach($userObjs as $userObj) {
    $user = get_user($userObj);
    $data = [];
    $country_name = get_country_name($user->country);
    if($user->address1 && $user->city && $user->country) {
      $address = implode(",", array_filter([$user->address1, $user->address2, trim("{$user->zip} {$user->city}"), $user->state, $country_name]));
      $data['address_formatted'] = $address;
      
      list($status, $acc, $lat, $lng, $bounds) = google_geocode($address);
      
      if($status==200) {
        $scope->http_code = "200"; //override error set in set_env.inc due to unknown slug
        $center = [$lat, $lng];
        $locObj = center2loc($center);
        $boundsObj = $bounds ? json_decode($bounds) : radius2bounds($locObj, DEFAULT_RADIUS);
        $bounds = any2bounds($boundsObj, true);
        
        $data['location_lat'] = $lat;
        $data['location_long'] = $lng;
        $data['location_bounds'] = json_encode($bounds);
        
        list($id, $errors) = update_object('user_profile', $data, $user->profile_id);
        echo("Updated $id with ".dump($data,true));
      }
    }
  }
}

/** new functions for template based layout */

/** hack for now to update maps with media data */
function update_media_collection_maps() {
  db_query("update media,gallery set media.artist_id=gallery.user_id where media.parent_type='gallery' and media.parent_id=gallery.id");
  db_query("update media_collection_map,media set media_collection_map.name=media.name,media_collection_map.artist_id=media.artist_id,media_collection_map.original_year=media.original_year,media_collection_map.original_technique=media.original_technique where media_collection_map.media_id = media.id");
  db_query("update media_collection_map,user_profile set media_collection_map.artist_name=user_profile.display_name where media_collection_map.artist_id = user_profile.user_id");
  db_query("update media_collection_map,user_profile set media_collection_map.curator_name=user_profile.display_name where media_collection_map.curator_id = user_profile.user_id");
  return "OK, updated gallery data";
}

// returns src of collection
function collection_title_image($collectionObjOrId, $options=NULL) {
  $collectionObj = any2obj('media_collection', $collectionObjOrId);
  if(!$collectionObj) return '';
  if($media_id = $collectionObj->title_image) return get_media_source($media_id, $options);
  $media_id = find_object('media_collection_map', array('media_collection_id' => $collectionObj->id, 'active' => 1), 'media_id', array('sort' => 'rank'));
  if($media_id) return get_media_source($media_id, $options);
  return '';  
}

// returns src of folder
function folder_title_image($folderObjOrId, $options=NULL) {
  $folderObj = any2obj('gallery', $folderObjOrId);
  if(!$folderObj) return '';
  if($media_id = $folderObj->title_image) return get_media_source($media_id, $options);
  $media_id = find_object('media', array('parent_type' => 'gallery', 'parent_id' => $folderObj->id, 'active' => 1), 'id', array('sort' => 'rank'));
  if($media_id) return get_media_source($media_id, $options);
  return '';  
}

/** gets media object from mapObj and merges the two */
function get_artwork($mapObj_or_id) {
  $mapObj = any2obj('media_collection_map', $mapObj_or_id);
  $artObj = get_object('media', $mapObj->media_id);
  $media_id = $artObj->id;
  $artObj->media_id = $media_id;
  $artObj->map_id = $artObj->id = $mapObj->id;
  $keys = array('media_collection_id', 'user_id', 'rank');
  foreach($keys as $fld) $artObj->$fld = $mapObj->$fld;
  return $artObj;

}

function gallery_find_user_collection($siteObj_or_id, $userObj_or_id, $options='') {
  $siteObj = any2obj('site', $siteObj_or_id);
  $site_id = $siteObj->id;
  $userObj = any2obj('user', $userObj_or_id);
  if(!$userObj) {
    print_log("Could not find user for obj/id:".dump($userObj_or_id, true), 'gallery', LOG_LEVEL_ALWAYS);
    print_log("Stack: ".caller_stack(), 'gallery', LOG_LEVEL_ALWAYS);
    return false;    
  }
  
  $user_id = $userObj->id;
  $return = $options['return'];
  $collection_type = $options['collection_type'] ?: MEDIA_COLLECTION_TYPE_COLLECTION;
  $myCollectionObj = find_object('media_collection', array('site_id' => $site_id, 'user_id' => $user_id, 'type' => $collection_type, 'active' => 1));

    
  if(!$myCollectionObj) {
    print_log("Could not find collection for user $user_id", 'gallery', LOG_LEVEL_ALWAYS);
    $my_collection_id = gallery_add_user_collection($siteObj, $userObj); // else add collection
    $myCollectionObj = get_object('media_collection', $my_collection_id);
  }
  return $return == 'id' ? $myCollectionObj->id : $myCollectionObj;
}

function gallery_add_user_collection($siteObj_or_id, $userObj_or_id, $options=array()) {
  $siteObj = any2obj('site', $siteObj_or_id);
  $site_id = $siteObj->id;
  $userObj = any2obj('user', $userObj_or_id);
  $user_id = $userObj->id;
  $collection_type = $options['collection_type'] ?: MEDIA_COLLECTION_TYPE_COLLECTION;
  $collection_title = $options['collection_titlre'] ?: phrase('my_collection', CAPITALIZE);

  $colData['active'] = 1;
  $colData['site_id'] = $site_id;
  $colData['user_id'] = $user_id;
  $colData['type'] = $collection_type;
  $colData['title'] = $collection_title;
  list($collection_id, $errors) = add_object('media_collection', $colData);
  print_log("Adding personal collection for user $user_id", 'gallery', LOG_LEVEL_ALWAYS);
  
  if($errors) {
    //dump($errors);
  } else {
    $messages[] = "Added collection id=$collection_id<br>";
  }
  return $collection_id;
}

/** return list of mapObjs representing unique artwork for given collection ids */

function gallery_unique_artworks($collection_ids) {
  $mapObjs = find_objects('media_collection_map', array('media_collection_id' => $collection_ids, 'active' => 1));
  $media_ids = array();
  $objs = array();
  foreach($mapObjs as $mapObj) {
    $media_id = $mapObj->media_id;
    if($media_ids[$media_id]) continue;
    $media_ids[$media_id] = 1;
    $objs[] = $mapObj;
  }
  
  return $objs;  
}

/** finds first curator/exhibition/project for media_map_object */
function gallery_artwork_related($siteObj_or_id, $mapObj_or_id, $options = array()) {  
  $siteObj = any2obj('site', $siteObj_or_id);
  $mapObj = any2obj('media_collection_map', $mapObj_or_id);
  $media_id = $mapObj->media_id;   
  //$media_id = "1111111111111";
  $result = new stdClass;

  if(!$media_id) return $result;

  if($collection_ids = find_objects('media_collection_map', array('media_id' => $media_id), array('fields' => 'distinct media_collection_id'))) {
    $project     = find_object('media_collection', array('type' => MEDIA_COLLECTION_TYPE_PROJECT, 'id' => $collection_ids, 'active' => 1),  array('fields' => 'id'));
    $exhibition  = find_object('media_collection', array('type' => MEDIA_COLLECTION_TYPE_EXHIBITION, 'id' => $collection_ids, 'active' => 1),  array('fields' => 'id'));    
    $curator     = find_object('media_collection', array('type' => MEDIA_COLLECTION_TYPE_EXHIBITION, 'id' => $collection_ids, 'active' => 1),  array('fields' => 'user_id'));
    //$artists     = find_object('media_collection', array('type' => MEDIA_COLLECTION_TYPE_PROJECT, 'id' => $collection_ids, 'active' => 1),  array('fields' => 'user_id'));
  
    if($project) {
      $result->project_id = $project->id;
    }     
    if($curator) {
      $result->curator_id = $curator->user_id;
      $result->curator = get_user($curator->user_id);
    }     
    if($exhibition) {
      $result->exhibition_id = $exhibition->id;
      $result->exhibition = get_object('media_collection', $exhibition->id);
    }     
  }  
  return $result;
}


      //dump($related);
      /**
      if($collection_id = $obj->media_collection_id) {
        $collectionObj = get_object('media_collection', $collection_id);
        $collection_type = $collectionObj->type;
        echo("collection_id = $collection_id type=$collectionObj->type<br>");
        if($collection_type == MEDIA_COLLECTION_TYPE_EXHIBITION) {
          echo("type = Exhibition<br>");
          if($curator_id = $collectionObj->user_id) {
            echo("curator_id=$curator_id<br>");
            $scope->curator_id = $curator_id;
            $scope->curator = get_user($curator_id);
          }
        }
      }
      */
    

function gallery_explore($siteObj_or_id, $obj_type, $id, $options = array()) {
  global $u_id, $u_level;
  
  $obj = $obj_type && $id ? get_object($obj_type, $id) : null;
  $auth_edit = $obj ? gallery_auth_media($obj_type, $obj, $u_id) : false; 
  $edit = $auth_edit && $options['edit'];
  $embed = $auth_edit && $options['embed'];
  $sharing_id = $options['sharing_id'];
  $preview = $options['preview'];
  $tutorial_button = "";
    
  $siteObj = any2obj('site', $siteObj_or_id);  
  $site_id = $siteObj->id;
  $obj_id = $id;
  //if($obj_type == 'media_collection_map') {
  //  $obj_id = get_object('media_collection_map', $id, 'media_id');    
  //  $obj_type = 'media';
  //}
  $edit_obj_type = $obj_type;
  $edit_obj_id = $id;
  switch($obj_type) {
  case 'media_collection_map':
    $template = $edit ? '_gallery-artwork-form' : '_gallery-artwork-detail';
    $controller = 'gallery_artworks';
    $tutorial_button = 
    " <a class=\"btn btn-primary popup-iframe\" target=\"vimeo\" href=\"https://vimeo.com/145297358\">
      <i class=\"fa fa-play-circle margin-right\"></i>
      Editing Art
    </a>";
    
    break;
  case 'media_collection':
    if($id) {
      if($embed) {
        if($sharing_id) $template = $preview ? '_gallery-collection-embed-preview' : '_gallery-collection-embed-edit'; 
        else $template = '_gallery-collection-embed';      
      } else {
        $template = $edit ? '_gallery-collection-form' : '_gallery-collection-detail';
        //if($edit) $scope->uploader = object_media_uploader($obj_type, $obj_id, 'title_image');
      }
    } else {
      $template = '_gallery-collection-items.html';
      $template = 'gallery-collections.html';
    }
    $controller = 'gallery_collections';
    break;
  case 'user':
    $template = '_gallery-artwork-detail';
    $controller = 'gallery_artworks';
    break;
  case 'gallery':
    //die("GH: auth=$auth_edit options={$options['edit']} edit=$edit".dump($options, true));
    $template = $edit ? '_gallery-folder-form' : '_gallery-folder-detail';
    $controller = 'gallery_folder';
    $tutorial_button = 
    " <a class=\"btn btn-primary popup-iframe\" target=\"vimeo\" href=\"https://vimeo.com/128292540\">
      <i class=\"fa fa-play-circle margin-right\"></i>
      Tutorial - Adding and Removing Art
    </a>";
    
    break;
  case 'media':
    //$edit = $auth_edit;
    $template = $edit ? '_gallery-artwork-form' : '_gallery-artwork-detail';
    $controller = 'gallery_artworks';
    $tutorial_button = 
    " <a class=\"btn btn-primary popup-iframe\" target=\"vimeo\" href=\"https://vimeo.com/145297358\">
      <i class=\"fa fa-play-circle margin-right\"></i>
      Editing Art
    </a>";
    break;
  default:
    return "Gallery Explore: Invalid type $obj_type";
    break;
  }
  $scope = new stdClass;
  $scope->obj_type = $obj_type;
  $scope->obj_id = $obj_id;
  $scope->vault = 1;
  foreach($options as $k => $v) $scope->$k = $v;
  //if($sharing_id) {
  //  $scope->sharing_id = $sharing_id;
  //  $scope->preview = $preview;
  //}
  $pageObj = new stdClass;
  $pageObj->template = $template;
  $pageObj->controller = $controller;
  
  $output = '';
  $load_url = "/admin/app_data.php?oper=load-content&site_id=$site_id&user_level=$u_level&user_id=$u_id&obj_type=$obj_type&id=$id";      
  $preview_button = html_link("#", html_i('', "fa fa-arrow-left")." ".phrase('back_to_preview', CAPITALIZE), array('class' => 'btn btn-success ajax-loader', 'data-url' => $load_url, 'data-target' => '#cms_viewer'))." ";
  if($edit) {
    //$output .= $preview_button;    
  } else if($auth_edit) {
    if(!$embed) {
      $load_url = "/admin/app_data.php?oper=load-content&site_id=$site_id&user_level=$u_level&user_id=$u_id&obj_type=$edit_obj_type&id=$edit_obj_id&edit=1"; 
      $edit_button = html_link("#", html_i('', "fa fa-pencil")." ".phrase('edit', CAPITALIZE), array('class' => 'btn btn-success ajax-loader', 'data-url' => $load_url, 'data-target' => '#cms_viewer'));
      $output .= $edit_button;
    }
    if($obj_type == 'media_collection') {
      $class = $embed ? "visuallyhidden" : ""; /** we still need this link for reloading, but don't show it */
      $load_url = "/admin/app_data.php?oper=load-content&site_id=$site_id&user_level=$u_level&user_id=$u_id&obj_type=$edit_obj_type&id=$edit_obj_id&embed=1"; 
      //$embed_button = html_link("#", html_i('', "fa fa-link")." ".phrase('embed', CAPITALIZE), array('id' => 'embed_link', 'class' => "btn btn-success ajax-loader $class", 'data-url' => $load_url, 'data-target' => '#cms_viewer'));
      $embed_button = html_link(site_page_link($siteObj, PAGE_PLUGIN)."?pt={$edit_obj_type}&pid={$edit_obj_id}", html_i('', "fa fa-link")." ".phrase('embed', CAPITALIZE), array('id' => 'embed_link', 'class' => "btn btn-success", 'target' => 'embed'));
      $output .= " ".$embed_button;
    }
  }

  
  if($edit || $embed) $output .= $preview_button;
  $output .= $tutorial_button;
  $output .= fetch_template($siteObj, $pageObj, array('scope' => $scope));
  //$output .= "gallery_explore: $obj_type $obj_id";
  return $output;
} 

 

function gallery_title_text($siteObj, $search, $options=NULL) {
  $obj_type = $search['obj_type'];
  $id       = $search['id'];
  $text = '';
  switch($obj_type) {
    case 'media': // single image from database      
      $obj = $imageObj = get_object($obj_type, $id);


      $year = $imageObj->original_year;
      $h = $imageObj->original_height;
      $w = $imageObj->original_width;
      $currency = $imageObj->original_currency ?: 'EUR';
      $price = $imageObj->original_price;
      
      if($imageObj->name) $text .= html_h3($imageObj->name.($year ? " ($year)" : ''));
      
      $orgArray = array();
      
      if($technique = $imageObj->original_technique) $text .= html_h4($technique);
      if($h > 0 && $w > 0) {
        $h_in = round($h / 2.54);
        $w_in = round($w / 2.54);
        $text .= phrase('height', CAPITALIZE).": ".$h."cm ($h_in\")"." x ".phrase('width', CAPITALIZE).": ".$w."cm ($w_in\")";
      }
      
      $count_str = $price_str = $available_str = $count_str = $dot = '';
      if($currency && $price > 0) $orgArray[]= get_currency_symbol($currency, true).formatFloat($price);
      $count = $imageObj->original_count;
      if($count > 0) $orgArray[]= $count > 1 ? "Series of $count" : "Original of one";    
      $available = $imageObj->original_available;
      $original_help_text = '';
      if($available == DB_YES) {
        $original_help_text = "Interested in the original? Please contact the curator and/or the artist for the latest information about price and availability, both of which may be subject to change.";
        $orgArray[]= 'Original available';
        $dot = html_span('&#x25cf;', 'dot_outside green');
      } elseif($available == DB_NO) {
        $dot = html_span('&#x25cf;', 'dot_outside red');
      } else {
        $dot = '';
      }
  
      $text .= html_div($dot.implode(', ', $orgArray), 'relative');
      
      //if($sd = $imageObj->original_technique ?: $imageObj->short_description) $text .= html_h4($sd);
      if($artist_name) {
        $artistAr = array_filter(array($artist_name,$artist_link,$artist_email));      
        $text .= html_div(phrase('artist', CAPITALIZE).': '.implode(', ', $artistAr));
      }
      if($curator_name) {
        $curatorAr = array_filter(array($curator_name,$curator_link,$curator_email));      
        $text .= html_div(phrase('curator', CAPITALIZE).': '.implode(', ', $curatorAr));
      }
      if($curatorObj) {
        //$text .= html_h4($imageObj->short_description);
      }
      
      if($desc = $imageObj->comment) $text .= html_p($desc);
      if($original_help_text) $text .= html_div($original_help_text, 'margin-top margin-bottom small-text'); 

      break;
    case 'gallery': // single image from database
      $obj = get_object($obj_type, $id);
      $text = html_h2($obj->title);
      $text .= html_p($obj->description);      
      break;
    case 'artist': // single image from database
      $text = user_profile_text($siteObj, $id, $options);
      break;
    default:
      break;
  }
  return $text;      
}

// uploader for new dynatree cms
function gallery_uploader($galleryObj_or_id, $options = array()) {
  global $u_id, $site_id,$u_level;
  $galleryObj = any2obj('gallery', $galleryObj_or_id);
  $gallery_id = $galleryObj->id;
  
  $class_attrs = get_object_attributes('gallery', false);
  $upload_options = $class_attrs['media'][ATT_LENGTH];
  $upload_options['minimum_size'] = array(1080, 1920); // either short side >= 1080 or long side >= 1920
  $fld = 'media';
  $val = $galleryObj->media;
     
  $mediaData['user_id'] = $u_id ?: $galleryObj->user_id;
  $mediaData['artist_id'] = $galleryObj->user_id;
  $mediaData['parent_id'] = $gallery_id;
  $mediaData['parent_type'] = 'gallery';
  $mediaData['parent_field'] = 'media';

  //$handler_options = array('handler' => 'cms_media_handler', 'handler_operation' => 'new-gallery-folder', 'target' => 'ajax_messages');
  
  $upload_options['download_template'] = $options['download_template'] ?: "";
  
  $upload_options['media_data'] = $mediaData;
  $upload_options['data-value_list'] = $val;
  $upload_options['show_file_list'] = false;
  $upload_options['title'] = "Click or drag to upload digital content";
  //$upload_options['handler'] = 'cms_media_handler';
  
  $handler =isset($options['handler']) ? $options['handler'] : 'refreshActiveNode';
  if($upload_options['handler'] = $handler) {
    $handler_options = array();
    $upload_options['handler_options'] = $handler_options;
  }


  // add edit button to uploader
  $edit_url = "/admin/app_data.php?oper=load-content&site_id=$site_id&user_level=$u_level&user_id=$u_id&obj_type=media&edit=1"; // id will be appended
  $upload_options['edit_url'] = $edit_url;
  $upload_options['edit_target'] = '#cms_viewer';

  //dump($upload_options);
  $uploader = jquery_file_uploader("gallery-$gallery_id-$fld", $val, $upload_options);
  //$uploader = fine_uploader("gallery-$gallery_id-$fld", $val, $upload_options);
  return $uploader;
}

function gallery_auth_media($obj_type, $obj_or_id, $user_id) {  
  global $u_level;
  $obj = any2obj($obj_type, $obj_or_id);
  if($obj->user_id == $user_id) return true;
  $auth_edit = false;
  $user_level = $u_level ?: get_object('user', $user_id, 'level');
  $is_staff   = $user_level >= USER_LEVEL_STAFF;
  $is_admin   = $user_level >= USER_LEVEL_ADMIN;
  if($is_staff || $is_admin) return true;
  $is_curator = $user_id && user_has_role($user_id, USER_ROLE_CURATOR);
  $is_artist = $user_id && user_has_role($user_id, USER_ROLE_ARTIST);

  switch($obj_type) {
  case 'media':
      
    // temp: todo - mayday, hack for now to let all edit
    return true;
    
    $owner_id = $obj->user_id;
    $artist_id = $obj->artist_id;
    $is_owner   = $user_id && $owner_id && $owner_id == $user_id;
    $is_artist  = $user_id && $artist_id && $artist_id == $user_id;              
    $auth_edit = $is_staff || $is_owner || $is_artist ? 1 : 0;
    
    break;
  case 'gallery':
    $auth_edit = $obj->user_id == $user_id;
    break;
  case 'media_collection':
    $auth_edit = $obj->user_id == $user_id;
    break;
  case 'media_collection_map':
    $collection_user_id = get_object('media_collection', $obj->media_collection_id, 'user_id');
    $auth_edit = $collection_user_id == $user_id;
    break;
  default:
    break;
  }

  return $auth_edit;
}

function gallery_create_button($siteObj_or_id, $userObj_or_id, $options=NULL) {
  $siteObj = any2obj('site', $siteObj_or_id);
  $userObj = any2obj('user', $userObj_or_id);
  $data = array('site_id' => $siteObj->id, 'user_id' => $userObj->id);
  $folder_tip = "You must create folders in your studio in order to upload and organize your art into vPatina";
  $shared_tip = "You must create shared folders in order to share art with the galleries you collaborate with.";

  /**
  Share your digital editions with curators, or choose to display them<br>
                 on your profile page, by creating a shared folder and dragging your<br>
                 digital editions into it."; // phrase("text_cms_shared_folder_help")
                 */
                 
  $exhibit_tip = "You must create exhibition folders in order to create exhibitions that can be embedded on any website of your choice";
  /**
  Curate exhibitions, featuring a range of artists, by dragging<br>
                  digital editions to an Exhibition folder. These exhibitions can be<br>
                  imbedded on any website of your choice. "; // phrase("text_cms_exhibition_help")
                  */
                  
  if(user_has_role($userObj, USER_ROLE_ARTIST))  $items[] = html_link('#', html_span(' ', 'fontello icon-folder').phrase('folder', CAPITALIZE), array('class' => 'cms-create', 'id' => 'cms_create_folder', 'data-obj_type' => 'gallery', 'data-site_id' => $siteObj->id, 'data-user_id' => $userObj->id))." ".html_tooltip($folder_tip, "help");
  if(user_has_role($userObj, USER_ROLE_ARTIST))  $items[] = html_link('#', html_span(' ', 'fontello icon-export-2').phrase('shared_folder', CAPITALIZE), array('class' => 'cms-create', 'id' => 'cms_create_project', 'data-obj_type' => 'media_collection', 'data-type' => MEDIA_COLLECTION_TYPE_PROJECT, 'data-site_id' => $siteObj->id, 'data-user_id' => $userObj->id))." ".html_tooltip($shared_tip, "help");
  if(user_has_role($userObj, USER_ROLE_CURATOR)) $items[] = html_link('#', html_span(' ', 'fontello icon-picture').phrase('exhibition', CAPITALIZE), array('class' => 'cms-create', 'id' => 'cms_create_exhibition', 'data-obj_type' => 'media_collection', 'data-type' => MEDIA_COLLECTION_TYPE_EXHIBITION, 'data-site_id' => $siteObj->id, 'data-user_id' => $userObj->id))." ".html_tooltip($exhibit_tip, "help");
                                                                                                                                                                                                                                                                                
  //  $items[] = html_link($link, phrase('my_vault', CAPITALIZE));


  $menu = html_ul($items);
  

  $output = html_link('#', html_i('', 'fa fa-upload margin-right').phrase('create', CAPITALIZE), array('id' => 'cms-create-button', 'class' => 'btn btn-success toggle-div dropdown', 'data-toggle' => 'gallery-create-menu', 'title' => 'foo bar'));

  $output .= html_div($menu, 'user-menu ztop click_hide', "id='gallery-create-menu'");
  return html_div($output, 'user-info');
}

/** end new functions for template based layout */

function plugin_javascript($get) {
  $site_url = $_SERVER['HTTP_HOST'];
  $host_domains = explode(".", $site_url);
  $host_tld = array_shift($host_domains); // e.g. com
  $host_domain = implode('.', $host_domains);  
  $referer = $_SESSION['vp_referer'] = $_SERVER['HTTP_REFERER'];
  extract($get);
  
  $site_id = $_SESSION['site_id'];
  $siteObj = $_SESSION['siteObj'];
  $sharer_id = 0; // default - will show top frame if not set
  if(!$get) return("No input");
  
  $share_id = isset($_GET['shid']) ? $_GET['shid'] : 0;
  if($share_id) {
    $pluginObj = get_object('sharing');
    $sharer_id = $pluginObj->share_user_id ?: $pluginObj->user_id;
  }
  
  // the plugin
  $plugin = sharing_output($get, array('viewer' => 'photoswipe', 'referer' => $referer));
  if(!$plugin) return '';
  $plugin = str_replace(array("\n", '"'), array(' ', '\"'), $plugin); // escape double quotes;
  
  $g_host_protocol = $host_tld == 'www' ? 'https' : 'http';
  $g_site_url = "$g_host_protocol://".$site_url;
  $output = <<<EOF
// vPatina: referer=$referer

var d = new Date();
var ts = d.getTime();
var cache_bust = "?q=" + ts;
var g_list;
var g_cid = '';
var g_cids;
var g_keys;

var g_pswp = false;
var g_pswp_index = -1;
var g_site_url = '$g_site_url';
var g_aid = 10;
var g_site_id = '$site_id';
var g_user_id = '$u_id';
var g_sharer_id = '$sharer_id';
var g_host_protocol = '$g_host_protocol';
var g_host_tld = '$host_tld';
var g_host_domain = '$host_domain';
var g_client_protocol = document.location.protocol;
var g_follow = [];
var g_branch = '9d08da5';
var g_artists = {};
var g_json_data;
var g_local_file = '';
var g_local_data = '';
var g_plugin_options = '';
var g_popup_options = '';
var g_popup_buttons = '';
var g_popup_tabs = '';

// g_branch = 'master';
var production = false;
var git_sub = production ? 'cdn.' : '';

var domain = (g_client_protocol == 'https:' ? 'https://' : 'http://') + g_host_tld + '.' + g_host_domain;

var src1 = domain + '/afr/js/vp/vp.js' + cache_bust;
var src2 = "https://maps.googleapis.com/maps/api/js?key=AIzaSyDqzndmgSgkwaD6AEATZOkeEWUo4foizEo&libraries=places&language=en";

var style1 = domain + '/afr/js/vp/photoswipe.css?v=4.1.1-1.0.6';
var style2 = domain + '/afr/js/vp/default-skin/default-skin.css?v=4.1.1-1.0.6';
var style3 = domain + '/afr/js/vp/vp.css' + cache_bust;

/**
if(production) {
  var src = 'https://' + git_sub + 'rawgit.com/kjakman/PhotoSwipe/' + g_branch + '/dist/vp.min.js' + cache_bust;
  var style = 'https://' + git_sub + 'rawgit.com/kjakman/PhotoSwipe/' + g_branch + '/dist/vp.min.css' + cache_bust;
} else { 
  var style1 = domain + '/afr/js/vp/photoswipe.css?v=4.1.1-1.0.5';
  var style2 = domain + '/afr/js/vp/default-skin/default-skin.css?v=4.1.1-1.0.5' + '&q=' + ts;
  var style3 = domain + '/afr/js/vp/vp.css' + cache_bust;  
}
*/

var g_afr_xss_loaded;
var _gaq = _gaq || [];
(function() {
  if(g_afr_xss_loaded) {
    console.log("xss already loaded"); 
    vp_search_local();
    return false;
  } else {
  
    console.log("xss not loaded v2...");
    g_cids = {};
    g_json_data = {};
    g_list = {};
    g_keys = {};
    
    // add vp script
    var ga = document.createElement('script');
    ga.src = src1;
    ga.setAttribute('async', 'true');
    document.getElementsByTagName('head')[0].appendChild(ga);
    document.getElementsByTagName('body')[0].appendChild(ga);                    

    // add google map
    var ga = document.createElement('script');
    ga.src = src2;
    ga.setAttribute('async', 'true');
    document.getElementsByTagName('head')[0].appendChild(ga);
    document.getElementsByTagName('body')[0].appendChild(ga);                    
    
    /** insert css */
    vp_requestStylesheet(style1)
    vp_requestStylesheet(style2)
    vp_requestStylesheet(style3)
    // vp_requestStylesheet("//maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css");
    g_afr_xss_loaded = true;
    
    /** insert html - photoswipe container */
    var html = '<div class="pswp" tabindex="-1" role="dialog" aria-hidden="true"><div class="pswp__bg"></div><div class="pswp__scroll-wrap"><div class="pswp__container"><div class="pswp__item"></div><div class="pswp__item"></div><div class="pswp__item"></div></div><div class="pswp__ui pswp__ui--hidden"><div class="pswp__top-bar"><div class="pswp__counter"></div>' +
      '<button class="pswp__button pswp__button--close" title="Close (Esc)"></button>' +
      '<button class="pswp__button pswp__button--share" title="Share"></button><button class="pswp__button pswp__button--fs" title="Toggle fullscreen"></button>' +
      '<button class="pswp__button pswp__button--user" title="User" id="userBtn"></button>' +
      '<button class="pswp__button pswp__button--calendar" title="Calendar" id="calendarBtn"></button>' +
      '<button class="pswp__button pswp__button--chat" title="Chat" id="chatBtn"></button>' +
      '<button class="pswp__button pswp__button--like vp__favorite-link" title="Like" id="likeBtn"></button>' +
      '<button class="pswp__button pswp__button--info" title="Info" id="infoBtn"></button>' +
      '<button class="pswp__button pswp__button--contact" title="Contact" id="contactBtn"></button>' +
      '<button class="pswp__button pswp__button--map" title="Map" id="mapBtn"></button>' +
      '<button class="pswp__button pswp__button--zoom" title="Zoom in/out"></button>' +
      '<div class="pswp__preloader"><div class="pswp__preloader__icn"><div class="pswp__preloader__cut">' +
      '<div class="pswp__preloader__donut"></div></div></div></div></div><div class="pswp__share-modal pswp__share-modal--hidden pswp__single-tap"><div class="pswp__share-tooltip"></div></div>' +
      '<button class="pswp__button pswp__button--arrow--left" title="Previous (arrow left)"></button><button class="pswp__button pswp__button--arrow--right" title="Next (arrow right)"></button><div class="pswp__caption"><div class="pswp__caption__center"></div></div></div></div></div>';

    vp_appendHtml1(document.body, html);

    var modal = '<div id="myModal" class="vp__modal" style="display:none"><div class="vp__modal-header"><span class="vp__close" id="closeBtn">×</span></div><div class="vp__modal-content" id="vp__modal-content"></div></div>';
    vp_appendHtml1(document.body, modal);
 
  }
})();
document.write("$plugin");

console.log('wrote output...');
vp_search_local();

function vp_search_local() {
  if(typeof vp_search === "function") {
    vp_search();
  } else {
    console.log('vp_search not found');
  }
}

function vp_requestScript(script_url) {
  var script = document.createElement('script');
  script.setAttribute('src', script_url);
  script.setAttribute('type', 'text/javascript');
  document.getElementsByTagName('head')[0].appendChild(script);
}
function vp_requestStylesheet(stylesheet_url) {
  stylesheet = document.createElement("link");
  stylesheet.rel = "stylesheet";
  stylesheet.type = "text/css";
  stylesheet.href = stylesheet_url;
  stylesheet.media = "all";
  document.getElementsByTagName("head")[0].appendChild(stylesheet);
}
function vp_appendHtml1(el, str) {
  var div = document.createElement('div');
  div.innerHTML = str;
  while (div.children.length > 0) {
    el.appendChild(div.children[0]);
  }
}
EOF;
  return $output;  
}

// legacy
function sharing_output($input, $options = array()) {
  return plugin($input, $options);
}

function plugin($input, $options = array()) {
  global $__SITE;
  
  $preview = $options['preview'];
  if($referer = $options['referer']) $_SESSION['vp_referer'] = $referer;

  $pluginOptions = array();

  $url = $debug = '';
  
  $plugin_id = $input['shid'];
  $index = $input['index'];
  $plugin_id = 0;
  $style = '';
  
  if($plugin_id = $input['shid']) {
    $pluginObj = get_object('plugin', $plugin_id);
    if(!$pluginObj) return "Plugin ($plugin_id) not found";    
    $sharer_id = $pluginObj->share_user_id ?: $pluginObj->user_id;
    $siteObj = $pluginObj->site_id == $__SITE->id ? $__SITE : get_object('site', $pluginObj->site_id);
    $site_id = $siteObj->id;
    $site_url = site_full_url($siteObj);
    
    extract(obj2array($pluginObj));

    if(!$preview) db_query("UPDATE sharing SET count=count+1 WHERE id=$plugin_id");
    if($data_json = $pluginObj->data) {
      $data = json_decode($data_json, true);
      $product_id = $data['product_id'];
    }
    
    $container_id = '__vp_plugin-'.$plugin_id;

    // overrides from URL
    $title = $input['title'] ?: $pluginObj->title;
    $subtitle = $input['subtitle'] ?: $pluginObj->subtitle;
    $size = $input['size'] ?: $pluginObj->size;

    print_log("shid={$plugin_id} title={$title} sub={$subtitle} size={$size}", 'sharing', LOG_LEVEL_TEST);
    
  } else { /** not in use */
    extract($input); // assigns keys from input into local variables with same names
    $parent_id = pick_first($parent_id, $obj_id, $id);
    $parent_type = pick_first($parent_type, $type, $obj_type);
    $container_id = '__vp_plugin-'.$parent_type.'_'.$parent_id;
  }
  
  $client_id = $siteObj->client_id;  
  $style = $pluginObj->style;
  
  if(!$site_id) return "Sharing: missing site_id";
  if(!$parent_id) return "Sharing: missing obj_id";
  if(!$parent_type) return "Sharing: missing obj_type";
  if(!$type) $type = 'image';
  

  if($class) $pluginOptions['class'] .= " $class";
    
  
  $pluginOptions['viewer'] = $viewer;
  $pluginOptions['format'] = 'json';
  $pluginOptions['size'] = $size;
  $pluginOptions['full'] = true;

  $search = $data ?: array();
  $search['obj_type'] = $parent_type;
  $search['obj_id'] = $parent_id;
  $search['plugin_id'] = $plugin_id;
  $search['container_id'] = $container_id;      
  $searchData = json_encode($search);
  $pluginOptions['data-data'] = $searchData;

  if($url) {
    $pluginOptions['data-url'] = $url;
    $link = 'javascript:void(0);';
  }
  $title_class = "afr_sharing_title";

  $pluginOptions = ['id' => $container_id, 'data-data' => $searchData];
  if($style) $pluginOptions['style'] = $style;
  if($url) $pluginOptions['data-url'] = $url;
  
  
  if($preview) $pluginOptions['js'] = "onclick='alert(\"Viewer preview: Coming soon!\");return false;'";
  
  $pluginOptions['data-options'] =  $pluginObj->plugin_options;
  $pluginOptions['data-sharer_id'] =  $sharer_id;
  $pluginOptions['data-popup_options'] = $pluginObj->popup_options;
  
  $mapObjs = find_objects('media_collection_map', ['media_collection_id' => $pluginObj->parent_id], ['sort' => 'rank']);
  if(!$mapObjs) return "No media for {$parent_type} {$parent_id}";
  
  $object_tag = $pluginObj->object_tag ?: 'figure';

  $viewer = $options['viewer'] ?: 'photoswipe';     
  $pluginClass = "__vp-plugin-container vp-loader-{$viewer}";
  if($cc = $pluginObj->object_class) $pluginClass .= " $cc";
  
  switch($type) {
  case 'image':
    $title_image = $pluginObj->title_image;
    if($title_image) {
      if(isint($title_image)) {
        $images = array_find_key($mapObjs, 'media_id');
        if(in_array($title_image, $images)) $pluginOptions['data-index'] = $index = array_search($title_image, $images);
      }
    } else {
      $mapObj = $mapObjs[0];
      $title_image = $mapObj->media_id; // use first
    }
    
    $imageOptions = [];
    $imageOptions['class'] = $class = "__vp-plugin-image center-cropped";
        
    $size = $pluginObj->size ?: 'big';
    $src = print_media($title_image, ['size' => $size, 'source_only' => 1, 'full' => 1]);
    
    //$image = html_image($src, $title, $pluginOptions); 
    $image = html_image($src, $title, $imageOptions); 
        
    $hover_effect = $pluginObj->hover_effect ?: 'zoom';
    $spinner = "<div style=\"width:20px;height:20px;display:inline-block\"><img src=\"{$site_url}/images/spinner.gif\"></div>";
    switch($hover_effect) {
      case 'flip':
        $back_image = html_image($src, $title, ['class' => '__vp-flip-back-image']); 
        $plugin = "
        <div class=\"__vp-flip-container\" ontouchstart=\"this.classList.toggle('hover');\">
          <div class=\"__vp-flipper\">
            <div class=\"__vp-flip-front\">
              {$image}
            </div>
            <div class=\"__vp-flip-back __vp-plugin-hover\">
              {$back_image}
              <div class=\"__vp-flip-back-card\">
                <h2>{$title}</h2><br>
                <div>{$subtitle}</div><br>
                
                <a href=\"#\" class=\"__vp-info __vp-view-button\" id=\"__vp-view-button-{$plugin_id}\">{$spinner} Loading...</a>
              </div>                                                   
            </div>
          </div>
        </div>
        ";    
      break;
      case 'none':
        $plugin = "
        <div class=\"__vp-plugin\">
          <div class=\"__vp-plugin-image\">
            {$image}
          </div>
          <div class=\"__vp-plugin-title\">
            <h2>{$title}</h2><br>
            <div>{$subtitle}</div><br>
          </div>
        </div>
        ";    
        break;
      
      case 'zoom':
      default:
        $pluginClass .= " view view-tenth";        
        $plugin = "
        {$image}
        <div class=\"mask __vp-plugin-hover\">
          <h2>{$title}</h2><br>
          <div>{$subtitle}</div><br>
          <a href=\"#\" class=\"__vp-info __vp-view-button\" id=\"__vp-view-button-{$plugin_id}\">{$spinner} Loading...</a>
        </div>
        ";
      break;
    }
        
    break;
  case 'link':
    $plugin = html_link($link, $title, ["class" => "__vp-plugin-link"]);
    break;
  case 'button':
    $plugin = html_link($link, $title, ["class" => "__vp-plugin-button"]);
    break;
  default:
    break;
  }    
  
  $output = html_tag($object_tag, $plugin, $pluginClass, $pluginOptions);
  
  // wrap tag in container tag
  if($tag = $pluginObj->container_tag) {
    $class_str = $pluginObj->container_class ? " class=\"{$pluginObj->container_class}\"" : '';
    $output = "<$tag{$class_str}>{$output}</$tag>";
  }

  $debug = '';
  $log = "id={$pluginObj->id} collection: {$parent_id}<br>container_tag=$tag object_tag={$object_tag}<br>title: {$title_image} index=$index<br>type: {$type} hover:{$hover_effect}";
  print_log($log, 'sharing', LOG_LEVEL_TEST);
  if($_SESSION['dev']) $debug = $log;

  if($style) {
    $output .= ''; /** todo: style for this #id */
  }
  
  return $debug.$output;  
}
