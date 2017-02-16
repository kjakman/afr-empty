<?php

// class definitions

$nodeTypeArray = array();
//$nodeTypes = array_keys($__CLASSES);
//foreach($nodeTypes as $nodeType) $nodeTypeArray[$nodeType] = ucfirst($nodetype);  

$y = phrase('yes', CAPITALIZE);
$n = phrase('no', CAPITALIZE);
$r = phrase('required', CAPITALIZE);
$ynr = "$y/$n/$r";

$global_scope = [];

$rateTypeArray = array(''=>'', 'hour' => 'hour', 'day' => 'day', 'month' => 'month', 'total' => 'total', 'special' => 'special');  
$currencyArray = array('EUR' => 'Euro', 'USD' => 'US Dollar', 'GBP' =>'British Pound', 'BTC' => 'Bitcoin');
$db_type_array = array('mysql', 'pgsql', 'oci8', 'odbc', 'sybase', 'fbsql', 'ibase', 'ifx', 'msql', 'mssql'); // (These are pear supported dbs)
$arrivalTypeArray = array('' => phrase('select', CAPITALIZE).'...', 'air' => phrase('air', CAPITALIZE), 'car' => phrase('car', CAPITALIZE), 'train' => phrase('train', CAPITALIZE), 'bus' => phrase('bus', CAPITALIZE), 'boat' => phrase('boat', CAPITALIZE), 'other' => phrase('other', CAPITALIZE));
$langArray = array('en'=> 'English', 'nl' => 'Dutch', 'no' => 'Norwegian');  
$countryArray = cc_array("Select country...");
// $boatTypeArray = array('open'=>'Open Boat', 'classic'=>'Classic Canal Boat', 'canal' => 'Canal Boat', 'salon'=>'Salon Boat', 'steam' => 'Steam Boat', 'monumental'=>'Monumental Boat', 'self-operated'=>'Self operated',  'sail' => 'Sail Boat', 'barge' => 'Barge', 'ij' => 'IJ boat');

$salutationArray = array(''=>'', 'Mr.' => phrase('mr.', CAPITALIZE), 'Ms.'=>phrase('ms.', CAPITALIZE), 'Mrs.'=>phrase('mrs.', CAPITALIZE), 'Dr.'=>phrase('dr.', CAPITALIZE));
$locationArray = array('landmark'=>'Landmark', 'continent' => 'Continent', 'region' => 'Region', 'country' => 'Country', 'district' => 'District', 'city' => 'City', 'borough' => 'Borough', 'neighborhood'=> 'Neighborhood', 'location' => 'Location');
$reqTypeArray = $enqTypeArray = array('enquiry'=>'Enquiry', 'reservation'=>'Reservation');
$weekdaysArray = $_SESSION['weekdays'] = [0 => 'None', 1 => phrase('Monday'), 2 => phrase('Tuesday'), 3 => phrase('Wednesday'), 4 => phrase('Thursday'), 5 => phrase('Friday'), 6 => phrase('Saturday'), 7 => phrase('Sunday')];
$billtoArray = [0 => phrase('guest', CAPITALIZE), 1 => phrase('employer', CAPITALIZE), 2 => phrase('department', CAPITALIZE), 3 => phrase('agent', CAPITALIZE), 4 => phrase('other', CAPITALIZE)];

$global_scope['billto'] = $billtoArray;
$_SESSION['global_scope'] = $global_scope;

$resizeArray = $_SESSION['resize_array'] = array(
  'org' => array(0, 'org'), 
  'tiny'   => array($_SESSION['tiny_pic_width'] ?: 40, 'tiny', array('crop' => 1)),                        
  'thumb' =>  array($_SESSION['thumb_pic_width'] ?: 100, 'thumbs'),
  'square' => array($_SESSION['square_pic_width'] ?: 200, 'square', array('crop' => 1)),                        
  'small' =>  array($_SESSION['small_pic_width'] ?: 200, 'small'), 
  'medium' => array($_SESSION['medium_pic_width'] ?: 640, 'medium'), 
  'ig' =>     array($_SESSION['ig_pic_width'] ?: 640, 'ig', array('crop' => 1)), // instagram square
  'big'   =>  array($_SESSION['big_pic_width']   ?: 1280, 'big'), 
  'full'  =>  array($_SESSION['full_pic_width']  ?: 1920, 'full'));

$yes_no_req = array('' => $ynr, DB_YES => $y, DB_NO => $n, DB_REQUIRED => $r);
$actionArray  = array('list'=>'List','view'=>'View','add'=>'Add','edit'=>'Edit','del'=>'Delete');
$frequencyArray = array('instant' => phrase('instant', CAPITALIZE), 'daily' => phrase('daily', CAPITALIZE), 'weekly' => phrase('weekly', CAPITALIZE), 'monthly' => phrase('monthly', CAPITALIZE));
$sms_flags = array('New request' => SMS_FLAG_REQUEST, 'Confirmed Reservation' => SMS_FLAG_CONFIRMED, 'Cancellations' => SMS_FLAG_CANCELLED);

$db_types1 = array('', 'int', 'tinyint', 'smallint', 'mediumint', 'bigint', 'float', 'decimal', 'date', 'datetime', 'timestamp', 'time', 'char', 'varchar', 'binary', 'varbinary', 'text', 'blob', 'set', 'enum');
foreach($db_types1 as $db_type) $db_types[$db_type] = $db_type;

//$site_filters = $u_sites ? "id => ($u_sites)" : "";
$descriptionActionArray = array('' => 'Select Action', ACTION_PREPEND => 'Prepend', ACTION_APPEND => 'Append', ACTION_OVERWRITE => 'Overwrite');

$ui_themes = assoc_array(array('base','black-tie','blitzer','cupertino','dot-luv','excite-bike','hot-sneaks','humanity','mint-choc','redmond','smoothness','south-street','start','swanky-purse','trontastic','ui-darkness','ui-lightness','vader'));
$ui_frameworks = assoc_array(array('bootstrap','boilerplate', 'bootstrap-sass'));

$site_filters = $_SESSION['auth_sites'] ? array('site.id' => $_SESSION['auth_sites']) : '';

$reservation_media_options = $product_media_options = $event_media_options = $single_media_options = $user_media_options = $gallery_media_options = $property_media_options = $std_media_options = $std_image_options = array(
  'minimum_size' => 100, 
  'minimum_file_size' => '1K', 
  'maximum_file_size' => '100M', 
  'allow_multiple' => true, 
  'allowed_types' => array('image','audio','video'), 
  'resize' => 1
);
 

$event_media_options['allowed_types'] = array('image','video', 'audio', 'text', 'application');
$user_media_options['allowed_types'] = array('image','video');
$property_media_options['allowed_types'] = array('image','video');
$single_media_options['allow_multiple'] = $std_image_options['allow_multiple'] = false;
$reservation_media_options['resize'] = 0;
$reservation_media_options['allowed_types'] = array('image','video', 'audio', 'text', 'application');

$std_image_options['allowed_types'] = 'image';
$positionArray = array(0 => phrase('no', CAPITALIZE), POSITION_TOP => phrase('above', CAPITALIZE), POSITION_BOTTOM => phrase('below', CAPITALIZE), POSITION_RIGHT => phrase('right', CAPITALIZE), POSITION_LEFT => phrase('left', CAPITALIZE)); 
$shareTypeArray = array('' => phrase('select'), 'image' => phrase('image', CALITALIZE), 'link' => phrase('link', CALITALIZE), 'button' => phrase('button', CALITALIZE), 'frame' => phrase('frame', CALITALIZE), 'buy' => phrase('buy_now', CALITALIZE));

$passport_media_options = $std_image_options;
$passport_media_options['minimum_file_size'] = '1M';
$passport_media_options['minimum_size'] = '1024';
  
  
  $addressArray = 
  
  array(
     'salutation'=>        array('Salutation',        'valSelect', '', 0, $salutationArray),
     'first_name'=>        array('First Name',        'str',    '', AF_SEARCHABLE, 50),
     'infix'=>             array('Infix',             'str',    '', AF_SEARCHABLE, 20),
     'last_name'=>         array('Last Name',         'str',    '', AF_SEARCHABLE, 50),
     'email_address'=>     array('Email',             'email',  '', AF_SEARCHABLE|AF_HIDE_LIST, 128),
     'organization'=>      array('Organization',      'str',    '', AF_SEARCHABLE, 200),
     'title'=>             array('Title',             'str',    '', AF_HIDE_LIST, 30),
     'address1'=>          array('Address1',          'str',    '', AF_HIDE_LIST, 50),
     'address2'=>          array('Address2',          'str',    '', AF_HIDE_LIST, 50),
     'city'=>              array('City',              'str',    '', AF_HIDE_LIST, 50),
     'state'=>             array('State',             'str',    '', AF_HIDE_LIST, 50),
     'zip'=>               array('Postal code',       'str',    '', AF_HIDE_LIST, 10),
     'country'=>           array('Country',           'many2one', ATT_DEFAULT_COUNTRY, AF_SEARCHABLE|AF_FORCE_SELECT, 'countries'),
     'phone '=>            array('Phone',             'phone',  '', AF_HIDE_LIST, 20),
     'phone2'=>            array('Phone2',            'phone',  '', AF_HIDE_LIST, 20),
     'phone3'=>            array('Phone3',            'phone',  '', AF_HIDE_LIST, 20),
     'url_web'=>           array('Web',               'url',    '', AF_HIDE_LIST, 50),
     'facebook'=>          array('Facebook',          'url',    '', AF_HIDE_LIST, 255),
     'twitter'=>           array('Twitter',           'str',    '', AF_HIDE_LIST, 255),
     'address_formatted'=> array('Formatted Address', 'text',   '', AF_HIDE_LIST));

     

// begin class definitions  
$__CLASSES = array(                                

//   CLASS                          USER_LEVEL  GROUP TABLE KEY FLAGS DESCRIPTOR SORT  PARENT_CLASS PARENT_FIELD
//                                    0           1     2    3     4      5       6        7            8

// object model
    'class' =>                array(USER_LEVEL_SYSTEM, 'object_model', '', 'type', NF_CACHE, 'name', '', ''),
    'class_group' =>          array(USER_LEVEL_SYSTEM, 'object_model', '', 'name', NF_CACHE, 'name', '', ''),
    'attribute' =>            array(USER_LEVEL_SYSTEM, 'object_model', '', 'id', NF_CACHE,   'name', 'id', ''),
    'attribute_type' =>       array(USER_LEVEL_SYSTEM, 'object_model', '', 'name', NF_CACHE,   'name', '', ''),
    //'default_class' =>        array(USER_LEVEL_SYSTEM, 'object_model', '', '', 0, '', '', ''),

// system
    'dictionary' =>           array(USER_LEVEL_SYSTEM, 'system', '', '', 0, 'term language', '', ''), /** special caching */
    'security' =>             array(USER_LEVEL_SYSTEM, 'system', '', '', 0, '', '', ''),
    'changelog' =>            array(USER_LEVEL_SYSTEM, 'system', '', '', NF_NO_ACTIONS, '', '', ''),
    'mail_campaign' =>        array(USER_LEVEL_SYSTEM, 'system', '', '', NF_NO_ACTIONS, '', '', ''),      
    'mail_queue' =>           array(USER_LEVEL_SYSTEM, 'system', '', '', NF_NO_ACTIONS, '', '', ''),      
    'mail_log' =>             array(USER_LEVEL_SYSTEM, 'system', '', '', NF_NO_ACTIONS, '', '', ''),      
    'sms_queue' =>            array(USER_LEVEL_SYSTEM, 'system', '', '', NF_NO_ACTIONS, '', '', ''),
    'exchange_rate' =>        array(USER_LEVEL_SYSTEM, 'system', '', '', 0, '', '', ''),
    'language' =>             array(USER_LEVEL_SYSTEM, 'system', '', 'code', NF_CACHE, '', '', ''),
    'currency' =>             array(USER_LEVEL_SYSTEM, 'system', '', 'code', NF_CACHE, 'code', 'code', ''),
    'countries' =>            array(USER_LEVEL_SYSTEM, 'system', '', '', NF_CACHE, '', 'name', ''),
    'weekday' =>              array(USER_LEVEL_SYSTEM, 'system', '', '', NF_CACHE, '', 'name', ''),
    'gender' =>               array(USER_LEVEL_SYSTEM, 'system', '', '', NF_CACHE, '', 'name', ''),
    'access_token' =>         array(USER_LEVEL_SYSTEM, 'system', '', '', 0, '', '', ''),
    'mime_type' =>            array(USER_LEVEL_SYSTEM, 'system', '', 'extension', 0, '', 'mime', ''),
    'description_type' =>     array(USER_LEVEL_SYSTEM, 'system', '', '', NF_CACHE_ASSOC, '', '', ''),
    'address' =>              array(USER_LEVEL_SYSTEM, 'system', '', '', NF_NO_DELETE|NF_NO_LIST, 'first_name,last_name,address1,city', '', ''),
    'address_type' =>         array(USER_LEVEL_SYSTEM, 'system', '', '', NF_CACHE_ASSOC, '', '', ''),
    'phone_type' =>           array(USER_LEVEL_SYSTEM, 'system', '', '', NF_CACHE_ASSOC, '', '', ''),
    'source' =>               array(USER_LEVEL_SYSTEM, 'system', '', '', 0, '', '', ''),
    'client' =>               array(USER_LEVEL_SYSTEM, 'system', '', '', 0, '', '', ''),
    'legal_entity' =>         array(USER_LEVEL_SYSTEM, 'system', '', '', 0, '', '', ''),
    'media' =>                array(USER_LEVEL_USER,   'system', '', '', NF_NO_LIST, '', 'rank', ''),
    'db_sequence' =>          array(USER_LEVEL_SYSTEM, 'system', '', 'seq_name', 0, 'seq_name', 'seq_name', ''),

// site
    'server' =>               array(USER_LEVEL_SYSTEM, 'site', '', '', NF_CACHE, 'name', '', ''),
    'site' =>                 array(USER_LEVEL_ADMIN, 'site', '', '', NF_CACHE|NF_COMPACT_LIST, 'domain', '', ''),
    'site_template' =>        array(USER_LEVEL_SYSTEM, 'site', '', '', 0, '', '', ''),
    'site_role' =>            array(USER_LEVEL_SYSTEM, 'site', '', '', NF_CACHE_ASSOC|NF_NO_ACTIONS, '', '', ''),
    'font' =>                 array(USER_LEVEL_SYSTEM, 'site', '', '', 0, '', '', ''),
    'site_page' =>            array(USER_LEVEL_STAFF,  'site', '', '', 0, '', 'parent_id, rank, id', ''),
    'page_content' =>         array(USER_LEVEL_STAFF,  'site', '', '', NF_NO_ADD, 'title', '', ''),
    'page_element' =>         array(USER_LEVEL_STAFF,  'site', '', '', 0, '', 'rank', ''),
    'page_type' =>            array(USER_LEVEL_SYSTEM, 'site', '', '', NF_CACHE|NF_CACHE_ASSOC, '', 'id', ''),

    'message' =>              array(USER_LEVEL_STAFF,  'site', '', '', 0, '', '', ''),
    'site_content' =>         array(USER_LEVEL_STAFF,  'site', '', '', 0, 'title', '', ''),
    'google_application' =>   array(USER_LEVEL_USER,   'site', '', '', 0, '', '', ''),

    'sharing' =>              array(USER_LEVEL_STAFF,  'social', '', '', 0, 'title', '', ''),
    'share_log' =>            array(USER_LEVEL_STAFF,  'social', '', '', 0, 'title', '', ''),

    'news' =>                 array(USER_LEVEL_STAFF,  'content', '', '', 0, 'title', '', ''),
    'article' =>              array(USER_LEVEL_USER,   'content', '', '', 0, 'title', 'created desc', ''),
    'comment' =>              array(USER_LEVEL_USER,   'content', '', '', 0, 'title', 'created desc', ''),
    'newsletter' =>           array(USER_LEVEL_USER,   'content', '', '', 0, 'email_address', 'created desc', ''),
    'object_description' =>   array(USER_LEVEL_STAFF, 'content', '', '', 0, '', '', ''),
    'article_type' =>         array(USER_LEVEL_USER,   'content', '', '', NF_CACHE_ASSOC, '', '', ''),
                                                                             
// gallery    
    'plugin' =>               array(USER_LEVEL_STAFF,  'gallery', '', '', 0, 'name', '', ''),
    'gallery' =>              array(USER_LEVEL_USER,   'gallery', '', '', 0, 'title', 'rank ', ''),
    'media_collection' =>     array(USER_LEVEL_USER,   'gallery', '', '', 0, 'title', 'rank ', ''),
    'media_collection_type' =>array(USER_LEVEL_USER,   'gallery', '', '', NF_CACHE_ASSOC, 'name', 'name ', ''),
    'media_collection_map' => array(USER_LEVEL_USER,   'gallery', '', '', 0, '', 'rank', ''),

// user                            

    'user' =>                 array(USER_LEVEL_SYSTEM, 'user', 'user', '', NF_NO_DELETE, 'username', '', ''),
    'user_level' =>           array(USER_LEVEL_SYSTEM, 'user', '', 'user_level', NF_CACHE_ASSOC, 'user_type', '', ''),
    'user_role' =>            array(USER_LEVEL_SYSTEM, 'user', '', '', NF_CACHE_ASSOC|NF_NO_ACTIONS, '', '', ''),
    'user_map' =>             array(USER_LEVEL_SYSTEM, 'user', '', '', 0, '', '', ''),
    'auth_log' =>             array(USER_LEVEL_SYSTEM, 'user', '', '', NF_NO_DELETE, 'display_name', '', ''),
    'user_profile' =>         array(USER_LEVEL_STAFF,  'user', '', '', 0, 'display_name', '', ''),
    'provider_profile' =>     array(USER_LEVEL_STAFF,  'user', '', '', 0, 'display_name', '', ''),
    'password_reset' =>       array(USER_LEVEL_SYSTEM, 'user', '', '', NF_NO_ACTIONS, '', '', ''),
    'wishlist' =>             array(USER_LEVEL_SYSTEM, 'user', '', '', 0, '', '', ''),

    
    'org' =>                  array(USER_LEVEL_STAFF,  'user', '', '', 0, 'org_name', 'org_name', ''),
    'contact' =>              array(USER_LEVEL_SYSTEM, 'user', '', '', 0, 'address.first_name,address.last_name,address.organization', '', ''),
    'agent' =>                array(USER_LEVEL_ADMIN,  'user', '', '', 0, 'name', '', ''),

    'contact_status' =>       array(USER_LEVEL_SYSTEM, 'user', '', '', NF_CACHE_ASSOC, '', '', ''),

    'provider' =>             array(USER_LEVEL_SYSTEM, 'user', '', '', 0, '', '', ''),
    'provider_key' =>         array(USER_LEVEL_SYSTEM, 'user', '', '', 0, '', '', ''),
    
// res
    'reservation' =>          array(USER_LEVEL_ADMIN, 'enquiry', '', 'res_id', NF_LOG|NF_COMPACT_LIST, '', '', ''),
    'special_offer' =>        array(USER_LEVEL_ADMIN,  'enquiry', '', '', NF_LOG|NF_COMPACT_LIST, '', '', ''),
    'res_status' =>           array(USER_LEVEL_SYSTEM, 'enquiry', '', '', NF_CACHE_ASSOC, '', '', ''),
    'res_type' =>             array(USER_LEVEL_SYSTEM, 'enquiry', '', '', NF_CACHE_ASSOC, '', '', ''),
    'rate_class' =>           array(USER_LEVEL_SYSTEM, 'enquiry', '', '', NF_CACHE_ASSOC, '', '', ''),
    'enq_status' =>           array(USER_LEVEL_SYSTEM, 'enquiry', '', '', 0, '', '', ''),
    'res_exception' =>        array(USER_LEVEL_SYSTEM, 'enquiry', '', '', 0, '', 'rank', ''),
    'chat' =>                 array(USER_LEVEL_SYSTEM, 'enquiry', '', '', NF_NO_ACTIONS, '', 'created DESC', ''),
    'feedback' =>             array(USER_LEVEL_SYSTEM, 'enquiry', '', '', 0, '', '', ''),
    'feedback_purpose' =>     array(USER_LEVEL_SYSTEM, 'enquiry', '', '', 0, 'name', 'id', ''),
    'feedback_profile' =>     array(USER_LEVEL_SYSTEM, 'enquiry', '', '', 0, 'name', 'id', ''),
    'price_breakdown'      => array(USER_LEVEL_USER,   'enquiry', '', '', 0, '', '', ''),
    'price_breakdown_row'  => array(USER_LEVEL_USER,   'enquiry', '', '', 0, '', 'date', ''),

// property
    'property' =>             array(USER_LEVEL_SYSTEM, 'property', '', '', 0, '', '', ''),
    'serviced_rental' =>      array(USER_LEVEL_OWNER,  'property', 'property', '', 0, '', '', 'property'),
    'shortstay' =>            array(USER_LEVEL_OWNER,  'property', 'property', '', 0, '', '', 'serviced_rental'),
    'facility' =>             array(USER_LEVEL_OWNER,  'property', 'facility', '', 0, '', '', ''),
    'property_description' => array(USER_LEVEL_OWNER,  'property', '', '', NF_NO_LIST, '', '', ''),
    'property_type' =>        array(USER_LEVEL_SYSTEM, 'property', '', '', NF_CACHE_ASSOC, '', '', ''),
    'hosting_property_type' => array(USER_LEVEL_SYSTEM, 'property', '', '', NF_CACHE_ASSOC, '', 'id', ''),
    'hosting_room_type'    => array(USER_LEVEL_SYSTEM, 'property', '', '', NF_CACHE_ASSOC, '', 'id', ''),
    'cancellation_policy' =>  array(USER_LEVEL_SYSTEM, 'property', '', '', NF_CACHE_ASSOC, '', 'id', ''),
    'checkin_time' =>         array(USER_LEVEL_SYSTEM, 'property', '', '', NF_CACHE_ASSOC, '', 'id', ''),
    'checkout_time' =>        array(USER_LEVEL_SYSTEM, 'property', '', '', NF_CACHE_ASSOC, '', 'id', ''),
    'calendar_import' =>      array(USER_LEVEL_OWNER,  'property', '', '', 0, '', 'id', ''),

// review
    'review' =>              array(USER_LEVEL_ADMIN,  'review', '', '', 0, '', 'id', ''),
    'review_item' =>         array(USER_LEVEL_ADMIN,  'review', '', '', 0, '', 'id', ''),
    'review_score' =>        array(USER_LEVEL_ADMIN,  'review', '', '', 0, '', 'id', ''),
                                    
// event
    'event' =>                array(USER_LEVEL_OWNER,  'event', '',      '', NF_LOG, '', '', ''),
    'checkin' =>              array(USER_LEVEL_OWNER,  'event', 'event', '', NF_LOG, '', '', 'event'),
    'checkout' =>             array(USER_LEVEL_OWNER,  'event', 'event', '', NF_LOG, '', '', 'event'),
    'cleaning' =>             array(USER_LEVEL_OWNER,  'event', 'event', '', NF_LOG, '', '', 'event'),
    'transport' =>            array(USER_LEVEL_OWNER,  'event', 'event', '', NF_LOG, '', '', 'event'),
    'maintenance' =>          array(USER_LEVEL_OWNER,  'event', 'event', '', NF_LOG, '', '', 'event'),
    'event_type' =>           array(USER_LEVEL_SYSTEM, 'event', '', '', NF_CACHE_ASSOC, '', '', ''),
    'event_status' =>         array(USER_LEVEL_SYSTEM, 'event', '', '', NF_CACHE_ASSOC, '', '', ''),

// product            
    'product' =>              array(USER_LEVEL_STAFF,  'product', '', '', 0, 'name', 'name', ''),
    'product_category' =>     array(USER_LEVEL_SYSTEM, 'product', '', '', 0, '', '', ''),    
    'product_option' =>       array(USER_LEVEL_STAFF,  'product', '', '', 0, '', '', ''),    
    'product_variant' =>      array(USER_LEVEL_STAFF,  'product', '', '', 0, '', '', ''),    
    'product_unit' =>         array(USER_LEVEL_SYSTEM, 'product', '', 'code', 0, '', 'code', ''),    
    'supplier' =>             array(USER_LEVEL_STAFF,  'product', '', '', 0, 'address.organization', 'address.organization', ''),
    'product_supplier_map' => array(USER_LEVEL_STAFF,  'product', '', '', 0, 'product_id', 'product_id', ''),
//    'cart'                 => array(USER_LEVEL_USER,   'product', '', '', 0, '', '', ''),
//    'cart_row'             => array(USER_LEVEL_USER,   'product', '', '', 0, '', '', ''),
    
// accounting
    'invoice' =>              array(USER_LEVEL_OWNER,  'accounting', '', '', NF_LOG|NF_COMPACT_LIST, '', '', ''),
    'inv_status' =>           array(USER_LEVEL_SYSTEM, 'accounting', '', '', NF_CACHE_ASSOC, '', '', ''),
    'inv_type' =>             array(USER_LEVEL_SYSTEM, 'accounting', '', '', NF_CACHE_ASSOC, '', '', ''),
    'inv_lineitem' =>         array(USER_LEVEL_SYSTEM, 'accounting', '', '', NF_LOG|NF_NO_LIST, '', 'type', ''),
    'lineitem_type' =>        array(USER_LEVEL_SYSTEM, 'accounting', '', '', NF_CACHE_ASSOC, 'name', '', ''),
    'payment' =>              array(USER_LEVEL_ADMIN,  'accounting', '', '', NF_LOG|NF_NO_ADD|NF_NO_DELETE, '', '', ''),
    'payment_type' =>         array(USER_LEVEL_SYSTEM, 'accounting', '', '', NF_CACHE_ASSOC, '', '', ''),
    'payment_source' =>       array(USER_LEVEL_SYSTEM, 'accounting', '', '', NF_CACHE_ASSOC, '', '', ''),
    'payment_status' =>       array(USER_LEVEL_SYSTEM, 'accounting', '', '', NF_CACHE_ASSOC, '', '', ''),
    'withdrawal' =>           array(USER_LEVEL_SYSTEM,    'accounting', '', '', NF_LOG|NF_NO_ADD|NF_NO_EDIT|NF_NO_DELETE, '', '', ''),
    'charge' =>               array(USER_LEVEL_SYSTEM,    'accounting', '', '', NF_LOG|NF_NO_ADD|NF_NO_EDIT|NF_NO_DELETE, '', '', ''),
    'gateway' =>              array(USER_LEVEL_SYSTEM,    'accounting', '', '', 0, 'name', '', ''),
    'transaction' =>          array(USER_LEVEL_SYSTEM,    'accounting', '', 'tx_id', NF_LOG|NF_NO_ACTIONS, '', '', ''),
    'tx_status' =>            array(USER_LEVEL_SYSTEM,    'accounting', '', '', NF_CACHE_ASSOC, '', '', ''),
    'cc' =>                   array(USER_LEVEL_SYSTEM,    'accounting', '', '', NF_NO_LIST, '', '', ''),
    'cc_type' =>              array(USER_LEVEL_SYSTEM,    'accounting', '', '', NF_CACHE_ASSOC, '', '', ''),
    'tax_category' =>         array(USER_LEVEL_SYSTEM, 'accounting', '', 'code', NF_CACHE_ASSOC, '', '', ''),
    'billing_period' =>       array(USER_LEVEL_SYSTEM, 'accounting', '', '', NF_CACHE_ASSOC, '', '', ''),
                                                                              

// location
    'country' =>              array(USER_LEVEL_SYSTEM, 'location', 'msCountry', '', NF_CACHE, '', '', ''),
    'geo_city' =>             array(USER_LEVEL_SYSTEM, 'location', 'geo_city', '', 0, 'name', 'name', ''),

    'landmark' =>             array(USER_LEVEL_STAFF,  'location', 'landmark'        , 'id', 0, '', '', ''),
    'landmark_type' =>        array(USER_LEVEL_STAFF,  'location', 'landmark_type'   , 'id', NF_CACHE_ASSOC, '', '', ''),
    'location' =>             array(USER_LEVEL_SYSTEM, 'location', 'location'        , 'id', 0, '', '', ''),
    'airport' =>              array(USER_LEVEL_SYSTEM, 'location', 'airport'         , 'id', 0, '', '', ''),

    'landmark_type' =>        array(USER_LEVEL_STAFF,  'location', 'landmark'        , 'id', NF_CACHE_ASSOC, '', '', ''),

//   Third Party                    USER_LEVEL  GROUP TABLE KEY FLAGS DESCRIPTOR SORT  PARENT_CLASS PARENT_FIELD
    'interhome_availability' => array(USER_LEVEL_SYSTEM,  'interhome', ''        , 'id', NF_CACHE, '', '', ''),
    'interhome_price'        => array(USER_LEVEL_SYSTEM,  'interhome', ''        , 'id', 0, '', '', ''),
    'interhome_service'      => array(USER_LEVEL_SYSTEM,  'interhome', ''        , 'id', 0, '', '', ''),

//   CLASS                          USER_LEVEL  GROUP TABLE KEY FLAGS DESCRIPTOR SORT  PARENT_CLASS PARENT_FIELD
    
    'pet_profile' =>          array(USER_LEVEL_USER,   'pet', '', '', 0, 'display_name', '', '', 249),
    'pet_type' =>             array(USER_LEVEL_SYSTEM, 'pet', '', '', NF_CACHE_ASSOC, 'name', 'name', '', 249),
    'pet_subtype' =>          array(USER_LEVEL_SYSTEM, 'pet', '', '', NF_CACHE_ASSOC, 'name', 'name', '', 249),

    'golf_region'      =>     array(USER_LEVEL_STAFF,  'golf', '', '', 0, '', '', '', 263),
    'golf_club'        =>     array(USER_LEVEL_STAFF,  'golf', '', '', 0, '', '', '', 263),
    'golf_course'      =>     array(USER_LEVEL_STAFF,  'golf', '', '', 0, '', '', '', 263),

);
// end class definitions

// begin class attributes

$__CLASS_ATTRIBUTES = array(                                

//   CLASS ATTRIBUTES                       0                  1       2       3            4          5
//   db field name                       Screen name          type   default flags  relation/options filters

  
  "cc" => 
  
  array(
     'id'=>                        array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'guest_id'=>                  array('Guest Id',          'link', ATT_DEFAULT_NULL, AF_HIDE_ADD|AF_READONLY|AF_SEARCHABLE, 'user'),
     'user_id'=>                   array('User Id',           'link', ATT_DEFAULT_USER_ID, AF_HIDE_ADD|AF_READONLY|AF_SEARCHABLE, 'user'),
     'site_id'=>                   array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_HIDE_LIST|AF_LOG, 'site'),
     'cc_type'=>                   array('Credit Card Type',  'many2one', 0, 1, 'cc_type'),
     'cc_number'=>                 array('Credit Card Number', 'cc',     0, AF_OBLIGATORY|AF_READONLY_EDIT, 20),
     'cc_crypt'=>                  array('CC crypt',           'cc',  0, AF_READONLY_EDIT|AF_ENCRYPT, 40),
     'cc_cardholder'=>             array('Cardholder full name','str',    '', 1, 50),
  //         'cc_exp_month'=>              array('Exp. Month',         'intSelect', 0, AF_OBLIGATORY, array(1,12,1)),
  //         'cc_exp_year'=>               array('Exp. Year',          'intSelect', 0, AF_OBLIGATORY, array(2009,2020,1)),
  
     'cc_exp_month'=>              array('Exp. Month',        'str',    '', 1, 2),
     'cc_exp_year'=>               array('Exp. Year',         'str',    '', 1, 4),
     'cc_cvv2'=>                   array('Security Code',     'str',    '', 0, 4),
     'last_charge' =>              array('Last charged',      'datetime',  ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),
  
     'charge'=>                    array('Charge log',        'one2many', 0, AF_HIDE_LIST|AF_READONLY, 'charge', 'cc_id'),
     'payments'=>                  array('Payments',          'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'payment', 'cc_id'),
     'remember'=>                  array('Store card?',        'bool', 0, AF_READONLY),
  
     'default_card' =>             array('Primary card?',      'bool',     0, AF_HIDE_LIST|AF_READONLY),
     
  ),
  
  /** new feedback */
  "review" => 
  
  array(

    
     'id'=>                        array('ID',                'id',          0, AF_HIDE_LIST|AF_PRIMARY|AF_AUTOINCREMENT),
     'created'=>                   array('Review Date',       'datetime',    ATT_DEFAULT_NOW, 0, 20),
     'active' =>                   array('Active?',           'bool',        1, AF_HIDE_LIST|AF_READONLY),
     'client_id'=>                 array('Client',    			  'link',        ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>                   array('Site',              'link',        ATT_DEFAULT_SITE_ID, AF_OBLIGATORY|AF_HIDE_LIST, 'site'),
     'user_id'=>                   array('User',              'link',        ATT_DEFAULT_USER_ID, AF_HIDE_ADD, 'user'),
     'host_id'=>                   array('Host',              'link',        0, AF_HIDE_ADD|AF_READONLY, 'user'),
     'guest_id'=>                  array('Guest',             'link',        0, AF_HIDE_ADD|AF_READONLY, 'user'),

     'source_id' =>                array('Source',             'link',        0, AF_HIDE_ADD|AF_READONLY, 'source'),
     'fid' =>                      array('Foreign ID',         'str',        0, AF_HIDE_ADD|AF_READONLY, 20),
     'source_url' =>               array('Source URL',         'url',         0, AF_HIDE_ADD|AF_READONLY),
     
     'parent_type'=>               array('Parent Type',       'parent_type', 0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD),
     'parent_id'=>                 array('Parent Id',         'parent_id',   0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD, 11),

     'reviewed_obj_type'=>         array('Reviewed Type',     'str',         0, AF_READONLY|AF_HIDE_ADD, 128),
     'reviewed_obj_id'=>           array('Reviewed Id',       'int',         0, AF_READONLY|AF_HIDE_ADD, 11),

     'language'=>                  array('Language',          'str',        '', AF_HIDE_LIST, 2),
     'published' =>                array('Published?',        'bool',        0, AF_HIDE_LIST|AF_READONLY),
     'anonymous' =>                array('Anonymous?',        'bool',        0, AF_HIDE_LIST|AF_READONLY),
     'helpful'=>                   array('# Helpful',         'int',         0, AF_READONLY, 4),
     'recommend'=>                 array('Recommend?',        'yesno',       0, AF_READONLY, 1),

     'reviewer_name' =>            array('Name',              'str',        '', 0, 128),
     'reviewer_city' =>            array('City',              'str',        '', 0, 128),
     'reviewer_state' =>           array('State',              'str',        '', 0, 32),
     'reviewer_country' =>         array('Country',           'str',        '', 0, 2),
     'reviewer_email' =>           array('Email',             'email',        '', 0, 128),                          
     'reviewer_phone' =>           array('Phone',             'phone',        '', 0, 16),
     
     'review_title' =>             array('Title',              'str',        '', 0, 128),
     'review_comment' =>           array('Comment',           'text',       '', AF_HIDE_LIST),
     'review_private' =>           array('Private feedback',   'text',       '', AF_HIDE_LIST),

     'media' =>                    array('Media',             'media',      '', 0, $single_media_options),
     'score' =>                    array('Score',             'float',        0, AF_HIDE_ADD, '2.2'),
  ),
  

  /** a review category for a given parent_type and a given site */
  "review_item" =>
  array(
     'id'=>            	    array('ID',                'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 128),
     'site_id'=>            array('Site',              'link',        ATT_DEFAULT_SITE_ID, AF_OBLIGATORY|AF_HIDE_LIST|AF_LOG, 'site'),
     'parent_type'=>        array('Parent Type',       'parent_type', 0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD, $reqTypeArray),
     'rank' =>              array('Rank',              'int', 0, 0, 6),
  ),
  
  /** the review of one category from one user 0-10 */
  "review_score" =>
  array(
     'id'=>            	    array('ID',                'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     
     /** below four duplicated for DB usability */
     'client_id'=>          array('Client',    			   'link',        ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>            array('Site',              'link',        ATT_DEFAULT_SITE_ID, AF_OBLIGATORY|AF_HIDE_LIST, 'site'),                            
     'parent_type'=>        array('Parent Type',       'parent_type', 0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD, $reqTypeArray),
     'parent_id'=>          array('Parent Id',         'parent_id',   0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD, 11),

     'review_id'=>          array('Review ID',         'link',  0, AF_OBLIGATORY|AF_HIDE_LIST|AF_LOG, 'review'),
     'review_item_id'=>     array('Review Item ID' ,   'link',  0, AF_OBLIGATORY|AF_HIDE_LIST|AF_LOG, 'review_item'),
     'score' =>             array('Score',             'int',   0, AF_HIDE_ADD),
  ),

  "feedback_purpose" =>
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
  ),
  "feedback_profile" =>
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
  ),

  "feedback" =>                                                                                       
  
  array(

    
     'id'=>                        array('ID',                'id',          0, AF_HIDE_LIST|AF_PRIMARY|AF_AUTOINCREMENT),
     'parent_id'=>                 array('Parent Id',         'parent_id',   0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD, 11),
     'parent_type'=>               array('Parent Type',       'parent_type', 0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD, $reqTypeArray),
     'apt_id' =>                   array('Property',          'link',        0, AF_HIDE_EDIT|AF_HIDE_ADD, 'property'),
     'city_id' =>                  array('City',              'link',        0, AF_HIDE_EDIT|AF_HIDE_ADD, 'geo_city'),
     'site_id'=>                   array('Site',              'many2one',   ATT_DEFAULT_SITE_ID, AF_OBLIGATORY|AF_HIDE_LIST|AF_LOG, 'site'),
     'page_id' =>                  array('Page',              'link',        0, AF_HIDE_EDIT|AF_HIDE_ADD, 'site_page'),
     'product_id' =>               array('Product',           'link',        0, AF_HIDE_EDIT|AF_HIDE_ADD, 'product'),
     'property_type'=>             array('Property Type',     'valSelect',   0, AF_READONLY, $propertyTypeArray),

     'source_id'=>                 array('Source',            'link',        ATT_DEFAULT_NULL, 0, 'source'),
     'source_url'=>                array('Source URL',        'url',         0, 0, 255),
     'fid'=>                       array('Foreign ID',        'str',         0, 0, 10),
     
     'user_id'=>                   array('User',              'link',        ATT_DEFAULT_USER_ID, AF_HIDE_ADD, 'user'),
//     'owner_id'=>                  array('Owner',             'link',        ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD, 'owner'),
     'host_id'=>                   array('Host',              'link', 0,     AF_HIDE_ADD|AF_READONLY, 'user'),
     'guest_id'=>                  array('Guest',             'link', 0,     AF_HIDE_ADD|AF_READONLY, 'user'),
     'agent_id'=>                  array('Agent',             'link',        ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'agent'),
     'client_id'=>                 array('Client',    			  'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
  
     'created'=>                   array('Review Date',       'datetime',    ATT_DEFAULT_NOW, 0, 20),
     'language'=>                  array('Language',          'str',    '', AF_HIDE_LIST, 2),
  
     'checkin'=>                   array('Checkin',           'date',   '', AF_HIDE_LIST, 50),
     'checkout'=>                  array('Checkout',          'date',   '', AF_HIDE_LIST, 50),
     'currency'=>                  array('Currency',          'valSelect', 0, AF_HIDE_LIST, $currencyArray),
     'total'=>                     array('Total',             'money',   0, AF_HIDE_LIST|AF_READONLY),
     'grand_total'=>               array('Grand Total',       'money',   0, AF_HIDE_LIST|AF_READONLY|AF_TOTAL),
     'num_days'=>                  array('# Days',            'int',    0, AF_READONLY, 4),
  //         'num_hours'=>                 array('# Hours',           'float',    0, AF_HIDE_LIST|AF_READONLY, '2.2'),
     'num_guests'=>                array('# Guests',          'intSelect', 0, 0, array(1,8,1, '')),
  
     'profile'=>                    array('Profile',          'many2one', 0, 0, 'feedback_profile'),
     'purpose'=>                    array('Purpose',          'many2one', 0, 0, 'feedback_purpose'),
     'ref'=>                        array('Referer',          'many2one', 0, AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'referer'),
     'ref_other'=>                  array('Ref (other)',      'str',    '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 20),
     'ref_searchterm'=>             array('Searchterm',       'str',    '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 50),
  
     'salutation'=>        array('Salutation',        'valSelect', '', 0, $salutationArray),
     'first_name'=>        array('First Name',        'str',    '', AF_SEARCHABLE, 50),
     'last_name'=>         array('Last Name',         'str',    '', AF_SEARCHABLE, 50),
     'email_address'=>     array('Email',             'email',  '', AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'city'=>              array('City',              'str',    '', AF_HIDE_LIST, 50),
     'state'=>             array('State',             'str',    '', AF_HIDE_LIST, 50),
     'country'=>           array('Country',           'valSelect', ATT_DEFAULT_COUNTRY, AF_SEARCHABLE, $countryArray),
  
  //         'feedback_website'    =>       array('Website'    , 'valSelect', 0, AF_READONLY, $ratingArray),
     'feedback_booking'    =>       array('Booking'    , 'int', 0, AF_READONLY),
     'feedback_pickup'     =>       array('Pickup'     , 'int', 0, AF_READONLY),
     'feedback_checkin'    =>       array('Checkin'    , 'int', 0, AF_READONLY),
     'feedback_catering'    =>      array('Catering'   , 'int', 0, AF_READONLY),
     'feedback_service'    =>       array('Service'    , 'int', 0, AF_READONLY),
     'feedback_location'   =>       array('Location'   , 'int', 0, AF_READONLY),
     'feedback_size'       =>       array('Size'       , 'int', 0, AF_READONLY),
     'feedback_decoration' =>       array('Decoration' , 'int', 0, AF_READONLY),
     'feedback_comfort'    =>       array('Comfort'    , 'int', 0, AF_READONLY),
     'feedback_cleaning'   =>       array('Cleaning'   , 'int', 0, AF_READONLY),
     'feedback_apps'       =>       array('Applicances', 'int', 0, AF_READONLY),
     'feedback_value'      =>       array('Value'      , 'int', 0, AF_READONLY),
     'feedback_overall'    =>       array('Score (0-10)'    , 'float', 0, 0, "2.1"),
   // 'feedback_overall'=>                array('Score (0-10)',          'intSelect', 0, AF_LOG, array(1,10,0.5, '')),

     'feedback_recommend'  =>       array('Recommend'  , 'bool', 0, AF_READONLY),
  
  //         'can_publish' =>               array('Can publish?', 'bool',     0, AF_HIDE_LIST|AF_READONLY),
     'published' =>                 array('Published?',   'bool',   0, AF_HIDE_LIST|AF_READONLY),
     'anonymous' =>                 array('Anonymous?',   'bool',   0, AF_HIDE_LIST|AF_READONLY),
     'helpful'=>                    array('# Helpful',    'int',    0, AF_READONLY, 4),

     'feedback_title' =>            array('Title',        'str',  '', 0, 128),
     'feedback_comments' =>         array('Comments',        'text',  '', AF_HIDE_LIST),
     'feedback_comments_neg' =>     array('Suggestions for improvement', 'text',  '', AF_HIDE_LIST),
     'feedback_private' =>          array('Private feedback', 'text',  '', AF_HIDE_LIST),

     'media' =>            array('Media',               'media', '', AF_HIDE_ADD, $single_media_options),
     
  ),
  
  
  "chat" => 
  
  array(
     'id'=>                        array('ID',                'id',   0, AF_HIDE_LIST|AF_PRIMARY|AF_AUTOINCREMENT),
     'parent_id'=>                 array('Parent Id',         'int',   0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD, 11),
     'parent_type'=>               array('Parent Type',       'str', 0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD),
     'created'=>                   array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY, 20),
     'timestamp'=>                 array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY, 20),
     'read_on'=>                   array('Read',              'datetime', ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_HIDE_ADD, 20),

     'status_change' =>            array('Status Change',     'link', 0, AF_HIDE_EDIT|AF_HIDE_ADD, 'res_status'),
     'special_offer_id' =>         array('Special Offer',     'link', 0, AF_HIDE_EDIT|AF_HIDE_ADD, 'special_offer'),

     'user_id' =>                  array('Author',            'link', ATT_DEFAULT_USER_ID, AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),
     'sender_id'=>                 array('Sender',            'link', 0, AF_SEARCHABLE|AF_READONLY, 'user'),
     'sender_level'=>              array('Sender Level',      'many2one', 0, AF_SEARCHABLE|AF_READONLY, 'user_level'),
     'receiver_id'=>               array('Recipient',         'link', 0, AF_SEARCHABLE|AF_READONLY, 'user'),
     'receiver_level'=>            array('Recipient Level',   'many2one', 0, AF_SEARCHABLE|AF_READONLY, 'user_level'),
     'thread' =>                   array('Thread',            'str', '', 0, 32),
     'notify'=>                    array('Notify',            'bool', 1, AF_HIDE_EDIT|AF_HIDE_ADD),
     'message'=>                   array('Message',           'text', '', AF_HIDE_EDIT|AF_OBLIGATORY|AF_HIDE_ADD),
     'language'=>                  array('Language',          'many2one',  ATT_DEFAULT_LANG, AF_HIDE_LIST, 'language'),
     
  ),
  
  "special_offer" => 
  
  array(
     'id'=>                        array('ID',                'id',   0, AF_HIDE_LIST|AF_PRIMARY|AF_AUTOINCREMENT),
     'created'=>                   array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY, 20),
     'timestamp'=>                 array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY, 20),
     'active' =>                   array('Active?',           'bool',     1, 0),
     
     'site_id'=>                   array('Site',    			    'link',    ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE, 'site'),
     'res_id' =>                   array('Reservation',       'link',     0, AF_OBLIGATORY|AF_HIDE_EDIT|AF_HIDE_ADD, 'reservation'),
     'user_id' =>                  array('Author',            'link', ATT_DEFAULT_USER_ID, AF_OBLIGATORY|AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),
     'host_id'=>                   array('Host',              'link',     0, AF_OBLIGATORY|AF_HIDE_ADD|AF_READONLY, 'user'),
     'guest_id'=>                  array('Guest',             'link',     0, AF_OBLIGATORY|AF_HIDE_ADD|AF_READONLY, 'user'),

     'property_type'=>             array('Property Type',     'valSelect', 0, AF_READONLY|AF_SEARCHABLE|AF_HIDE_ADD|AF_OBLIGATORY, $propertyTypeArray),
     'apt_id'=>                    array('Property ID',       'link', 0, AF_OBLIGATORY|AF_HIDE_ADD|AF_READONLY, 'user'),
     'num_guests'=>                array('# Guests',          'int', 0, AF_OBLIGATORY|AF_LOG),
     'num_days'=>                  array('# Days',            'int', 0, AF_OBLIGATORY),
     'checkin'=>                   array('Checkin',           'date',   '', AF_LOG),
     'checkout'=>                  array('Checkout',          'date',   '', AF_LOG),
                                   
     'currency'=>                  array('Currency',          'valSelect', 0, AF_OBLIGATORY|AF_HIDE_LIST|AF_LOG, $currencyArray),
     'rate_type'=>                 array('Rate Type',         'valSelect', 'day', AF_OBLIGATORY|AF_HIDE_LIST|AF_LOG, $rateTypeArray),
     'rate_base'=>                 array('Base Rate',         'money',   0, AF_OBLIGATORY|AF_HIDE_LIST|AF_LOG),
     
  ),
  

  "security" => 
  array(
     'id'=>                    array('ID',                'id',   0, AF_HIDE|AF_PRIMARY|AF_AUTOINCREMENT),
     'node'=>                  array('Node',          		'valSelect', 0, AF_SEARCHABLE|AF_OBLIGATORY, $nodeTypeArray),
     'action'=>                array('Action',          	'valSelect', 0, AF_SEARCHABLE|AF_OBLIGATORY, $actionArray),
     'user_level'=>            array('User Level',        'many2one',  0, AF_SEARCHABLE|AF_OBLIGATORY, 'user_level'),
  ),
  
  "event" => 
  
  array(
    'id' =>                        array('ID',                'id',   0, AF_SEARCHABLE|AF_PRIMARY|AF_AUTOINCREMENT),
    
    'active' =>                    array('Active?',           'bool',     1, 0),
    'client_id'=>                  array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
    'site_id'=>                    array('Site',    			    'link',     ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE, 'site'),
    'user_id' =>                   array('Author',            'link',     ATT_DEFAULT_USER_ID, AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),

    'host_id'=>                    array('Host',              'link',     0, AF_HIDE_ADD|AF_READONLY, 'user'),
    'parent_id'=>                 array('Parent Id',          'parent_id',   ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST, 11),
    'parent_type'=>               array('Parent Type',        'parent_type', ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST),
    'user_level'=>                 array('User Level',        'many2one', 0, 0, "user_level"),
    
    'created' =>                   array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY),
    'timestamp' =>                 array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),
    'type' =>                      array('Event type',        'many2one', 100, AF_OBLIGATORY|AF_SEARCHABLE, 'event_type'),
    'status' =>                    array('Status',            'many2one', EVENT_STATUS_UNCONFIRMED, AF_OBLIGATORY|AF_LOG|AF_SEARCHABLE , 'event_status'),
    'status_change_timestamp'=>    array('Status Changed on', 'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),

    'language'=>                   array('Language',          'many2one', ATT_DEFAULT_LANGUAGE, 0, 'language'),


    /** changed from name/notes */
    'title'=>                      array('Name',              'str',      '', AF_OBLIGATORY, 128),
    'description'=>                array('description',       'text',      '', AF_HIDE_LIST),

    'start_time' =>                array('Start',             'datetime', '', AF_OBLIGATORY|AF_SEARCHABLE|AF_LOG, 'end_time'), // options = dependent field
    'end_time' =>                  array('End',               'datetime', '', AF_OBLIGATORY|AF_SEARCHABLE|AF_LOG),
    'timezone' =>                  array('Timezone',          'timezone', ATT_DEFAULT_TIMEZONE, 0, 32),
    
    'start_address' =>             array('Location',          'text',     '', AF_SEARCHABLE|AF_LOG, 200),
    'end_address' =>               array('End Location',      'text',     '', AF_SEARCHABLE|AF_LOG, 200),
    'all_day' =>                   array('All day?',          'bool',     0, 0),

    'address_street'=>    array('Street',            'str',  '', AF_HIDE_LIST, 50 ),
    'address_number'=>    array('Number',            'str',  '', AF_HIDE_LIST, 12 ),
    'address_city'=>      array('City',              'str',  '', AF_HIDE_LIST, 50 ),
    'address_postcode'=>  array('Postcode',          'str',  '', AF_HIDE_LIST, 50 ),
    'address_state'=>     array('State',             'str',  '', AF_HIDE_LIST, 50 ),
    'address_country'=>   array('Country',           'link', '', AF_HIDE_LIST, 'countries'),
    'address_formatted'=> array('Adddress',          'text', '', AF_HIDE_LIST),

    'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
    'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
    'location_bounds' =>  array('Bounds',            'json', '', AF_HIDE_ADD|AF_HIDE_LIST),
    
    'num_hours'=>          array('# Hours',           'float',    0, AF_READONLY, '2.2'),
    'alert'=>              array('NB!',               'str',     '', AF_HIDE_LIST, 100),

    'booking_pin'=>                array('Booking PIN',       'str',    '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD|READONLY, 10),
    'media'                => array('Media',             'media',     '', 0, $event_media_options),

    /** not yet in use 
    'repeat_id' =>               array('Repeat ID',       'str',     '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 13),
    'repeat_interval' =>         array('Repeat Interval', 'str',     '', AF_HIDE_LIST, 4), // todo; add class, use many2one
    'repeat_until' =>            array('Repeat Until',    'datetime', '', AF_HIDE_LIST),
  
    'reminder_period1' =>         array('Reminder 1',       'str',      '', AF_HIDE_LIST, 6), // todo; add class, use many2one
    'reminder_time1' =>           array('Remdinder Time 1', 'datetime', ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),
    'reminder_sent1' =>           array('Remdinder Sent 1', 'bool',     0, AF_HIDE_LIST|AF_READONLY),
    'reminder_period2' =>         array('Reminder 2',       'str',      '', AF_HIDE_LIST, 6), // todo; add class, use many2one
    'reminder_time2' =>           array('Remdinder Time 2', 'datetime', ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),
    'reminder_sent2' =>           array('Remdinder Sent 2', 'bool',     0, AF_HIDE_LIST|AF_READONLY),
    'reminder_phone' =>          array('Reminder Phone',    'phone',    '', AF_HIDE_LIST, 20),
    'reminder_email' =>          array('Reminder email',    'email',    '', AF_HIDE_LIST, 20),        
    */
    
     
    ),
   
  // base class
/**  
  
  "event_old" => 
  
  array(
    'id' =>                        array('ID',                'id',   0, AF_SEARCHABLE|AF_PRIMARY|AF_AUTOINCREMENT),
    'res_id' =>                    array('Reservation',       'link',     0, AF_HIDE_EDIT|AF_HIDE_ADD, 'reservation'),
    'apt_id' =>                    array('Property',          'link',     0, AF_HIDE_EDIT|AF_HIDE_ADD, 'property'),

    'parent_id'=>                 array('Parent Id',         'parent_id',   ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST, 11),
    'parent_type'=>               array('Parent Type',       'parent_type', ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST),
    
    //    'owner_id'=>                   array('Owner',             'link',     0, AF_HIDE_ADD, 'owner'),
    'client_id'=>                  array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
    'site_id'=>                    array('Site',    			    'link',     ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE, 'site'),
    'user_id' =>                   array('Author',            'link',     ATT_DEFAULT_USER_ID, AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),

    'host_id'=>                    array('Host',              'link',     0, AF_HIDE_ADD|AF_READONLY, 'user'),
    'supplier_id'=>                array('Supplier',          'many2one',  ATT_DEFAULT_NULL, AF_HIDE_LIST, 'supplier'),
    'lineitem_id'=>                array('Invoice Lineitem',  'link',     ATT_DEFAULT_NULL, AF_HIDE_LIST, 'inv_lineitem'),
    'property_type'=>              array('Property Type',     'valSelect', 0, AF_READONLY, $propertyTypeArray),
    'type' =>                      array('Event type',        'many2one', 100, AF_OBLIGATORY|AF_SEARCHABLE, 'event_type'),
    'contractor_id' =>             array('Contractor',        'link',     0, 0, 'user'),
    //'author_id' =>                 array('Author',            'link',     ATT_DEFAULT_USER_ID, AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),
    'city_id' =>                   array('City',              'link',     0, AF_READONLY|AF_SEARCHABLE, 'geo_city', array('active' => 1), 'name'),
    'language'=>                   array('Language',          'many2one', ATT_DEFAULT_LANGUAGE, 0, 'language'),
    'status' =>                    array('Status',            'many2one', EVENT_STATUS_UNCONFIRMED, AF_OBLIGATORY|AF_LOG|AF_SEARCHABLE , 'event_status'),
    'status_change_timestamp'=>    array('Status Changed on', 'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),
    'created' =>                   array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY),
    'timestamp' =>                 array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),

     // below are "new", for generic events
    'active' =>                    array('Active?',           'bool',     1, 0),
    'user_level'=>                 array('User Level',         'many2one', 0, 0, "user_level"),
    'name'=>                       array('Name',              'str',      '', AF_OBLIGATORY, 100),
    'start_time' =>                array('Start',             'datetime', '', AF_OBLIGATORY|AF_SEARCHABLE|AF_LOG, 'end_time'), // options = dependent field
    'end_time' =>                  array('End',               'datetime', '', AF_OBLIGATORY|AF_SEARCHABLE|AF_LOG),
    'timezone' =>                  array('Timezone',          'timezone', ATT_DEFAULT_TIMEZONE, 0, 32),
    
    'start_address' =>             array('Location',          'text',     '', AF_SEARCHABLE|AF_LOG, 200),
    'end_address' =>               array('End Location',      'text',     '', AF_SEARCHABLE|AF_LOG, 200),
    'notes'=>                      array('Our Notes',         'text',     '', AF_HIDE_LIST),
    'all_day' =>                   array('All day?',          'bool',     0, 0),

    'address_street'=>    array('Street',            'str',  '', AF_HIDE_LIST, 50 ),
    'address_number'=>    array('Number',            'str',  '', AF_HIDE_LIST, 12 ),
    'address_city'=>      array('City',              'str',  '', AF_HIDE_LIST, 50 ),
    'address_postcode'=>  array('Postcode',          'str',  '', AF_HIDE_LIST, 50 ),
    'address_state'=>     array('State',             'str',  '', AF_HIDE_LIST, 50 ),
    'address_country'=>   array('Country',           'link', '', AF_HIDE_LIST, 'countries'),
    'address_formatted'=> array('Adddress',          'text', '', AF_HIDE_LIST),

     'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
    'location_bounds' =>  array('Bounds',            'json', '', AF_HIDE_ADD|AF_HIDE_LIST),
    
    'num_hours'=>                  array('# Hours',           'float',    0, AF_READONLY, '2.2'),
    'alert'=>                      array('NB!',               'str',     '', AF_HIDE_LIST, 100),

    'start_landmark_id' =>         array('Start Location',    'many2one',  '', AF_SEARCHABLE|AF_LOG, 'landmark'),
    'end_landmark_id' =>           array('End Location',      'many2one',  '', AF_SEARCHABLE|AF_LOG, 'landmark'),
  
    'contractor_name' =>          array('Contractor Name',  'str',     '', 0, 50),
    'contractor_notes' =>         array('Contractor Notes',  'str',     '', 0, 200),
  
    'customer_name' =>           array('Customer Name',   'str',     '', 0, 100),
    'customer_count' =>          array('Customer Count',  'int',     0, 0, 2),
    'customer_notes' =>          array('Customer Notes',  'text',    '', 0, 200),
  
    'repeat_id' =>               array('Repeat ID',       'str',     '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 13),
    'repeat_interval' =>         array('Repeat Interval', 'str',     '', AF_HIDE_LIST, 4), // todo; add class, use many2one
    'repeat_until' =>            array('Repeat Until',    'datetime', '', AF_HIDE_LIST),
  
    'reminder_period1' =>         array('Reminder 1',       'str',      '', AF_HIDE_LIST, 6), // todo; add class, use many2one
    'reminder_time1' =>           array('Remdinder Time 1', 'datetime', ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),
    'reminder_sent1' =>           array('Remdinder Sent 1', 'bool',     0, AF_HIDE_LIST|AF_READONLY),
    'reminder_period2' =>         array('Reminder 2',       'str',      '', AF_HIDE_LIST, 6), // todo; add class, use many2one
    'reminder_time2' =>           array('Remdinder Time 2', 'datetime', ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),
    'reminder_sent2' =>           array('Remdinder Sent 2', 'bool',     0, AF_HIDE_LIST|AF_READONLY),
    'reminder_phone' =>          array('Reminder Phone',    'phone',    '', AF_HIDE_LIST, 20),
    'reminder_email' =>          array('Reminder email',    'email',    '', AF_HIDE_LIST, 20),        
  
    'ticket_currency'=>         array('Currency',        'valSelect', 0, AF_HIDE_LIST|AF_LOG, $currencyArray),
    'ticket_price'=>            array('Price',           'money',     0, AF_HIDE_LIST|AF_LOG),
    'ticket_discount'=>         array('Discount',        'discount',  0, AF_HIDE_LIST|AF_LOG),
  
    'booking_pin'=>                array('Booking PIN',       'str',    '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD|READONLY, 10),
    'media'                => array('Media',             'media',     '', 0, $event_media_options),
     
    ),
  
  
  "checkin" => 
  array(
    'type' =>               array('Event type',        'many2one', EVENT_TYPE_CHECKIN, AF_OBLIGATORY|AF_SEARCHABLE|AF_HIDE_ADD|AF_READONLY_EDIT, 'event_type'),
    'contractor_notes' =>   array('Checkin Notes',     'str',      '', 0, 200),
    'start_address' =>      array('Checkin Address',   'text',     '', AF_SEARCHABLE|AF_LOG, 200),
    'end_address' =>        array('End Address',       'text',     '', AF_SEARCHABLE|AF_LOG|AF_HIDE, 200),
  ),
  
  "checkout" => 

  array(
    'type' =>               array('Event type',        'many2one', EVENT_TYPE_CHECKOUT, AF_OBLIGATORY|AF_SEARCHABLE|AF_HIDE_ADD|AF_READONLY_EDIT, 'event_type'),
    'contractor_notes' =>   array('Checkout Notes',    'str',     '', 0, 200),
    'start_address' =>      array('Checkout Address',  'text',    '', AF_SEARCHABLE|AF_LOG, 200),
    'end_address' =>        array('End Address',       'text',    '', AF_SEARCHABLE|AF_LOG|AF_HIDE, 200),
  ),
  
  "maintenance" => 
  array(
    'type' =>               array('Event type',          'many2one', EVENT_TYPE_MAINTENANCE, AF_OBLIGATORY|AF_SEARCHABLE|AF_HIDE_ADD|AF_READONLY_EDIT, 'event_type'),
    'apt_id' =>             array('Property',            'link',     0, AF_HIDE_EDIT|AF_HIDE_ADD|AF_OBLIGATORY, 'property'),
    'contractor_notes' =>   array('Maintenance Notes',   'str',     '', 0, 200),
    'start_address' =>      array('Maintenance Address', 'text',      '', AF_SEARCHABLE|AF_LOG, 200),
    'end_address' =>        array('End Address',         'text',      '', AF_SEARCHABLE|AF_LOG|AF_HIDE, 200),
  ),
  
  "cleaning" =>      
  array(
    'type' =>               array('Event type',        'many2one', EVENT_TYPE_CLEANING, AF_OBLIGATORY|AF_SEARCHABLE|AF_HIDE_ADD|AF_READONLY_EDIT, 'event_type'),
    'contractor_notes' =>   array('Cleaning Notes',    'str',     '', 0, 200),
    'start_address' =>      array('Cleaning Address',  'text',      '', AF_SEARCHABLE|AF_LOG, 200),
    'end_address' =>        array('End Address',       'text',      '', AF_SEARCHABLE|AF_LOG|AF_HIDE, 200),
  ),
  
  "transport" => 
  array(
    'type' =>               array('Event type',        'many2one', EVENT_TYPE_TRANSPORT, AF_OBLIGATORY|AF_SEARCHABLE|AF_HIDE_ADD|AF_READONLY_EDIT, 'event_type'),
    'contractor_notes' =>   array('Transport Notes',   'str',     '', 0, 200),
    'start_address' =>      array('Pickup Address',    'text',      '', AF_SEARCHABLE|AF_LOG, 200),
    'end_address' =>        array('Dropoff Address',   'text',      '', AF_SEARCHABLE|AF_LOG, 200),
  ),
*/

  
  "reservation" => 
  
  array(
     'res_id'=>                    array('ID',                'id', 0, AF_SEARCHABLE|AF_PRIMARY|AF_AUTOINCREMENT),
     'site_id'=>                   array('Site',              'many2one',   ATT_DEFAULT_SITE_ID, AF_LOG|AF_SEARCHABLE, 'site'),
     'status'=>                    array('Status',            'many2one',   STATUS_DRAFT, AF_OBLIGATORY|AF_LOG|AF_SEARCHABLE , 'res_status'),
     'type'=>                      array('Type',              'many2one',   5, AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD|AF_LOG, 'res_type'),
     'event_id'=>                  array('Event ID',          'link', 0, AF_HIDE_LIST, 'event'),
     'client_id'=>                 array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'source_id'=>                 array('Source',    			  'many2one', ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_LIST|AF_HIDE_ADD|AF_HIDE_EDIT, 'source'),
     'dest_id'=>                   array('Destination',    	  'many2one', ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_LIST|AF_HIDE_ADD|AF_HIDE_EDIT, 'source'),
     'fid'=>                       array('Foreign ID',        'str',  ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_LIST|AF_HIDE_ADD|AF_HIDE_EDIT, 20),
     'fids'                     => array('Foreign IDs'       ,'json', '', AF_HIDE_LIST|AF_HIDE_ADD, 255),
     'fgid'=>                      array('Foreign Guest ID',  'str',  ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_LIST|AF_HIDE_ADD|AF_HIDE_EDIT, 20),
     'property_type'=>             array('Property Type',     'valSelect', 0, AF_OBLIGATORY|AF_READONLY|AF_SEARCHABLE, $propertyTypeArray),
     'corporate'=>                 array('Corporate?',        'bool', 0, AF_READONLY),
     'created'=>                   array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY),
     'timestamp'=>                 array('Modified',          'timestamp',  ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY),
     'status_change_timestamp'=>   array('Status Changed on', 'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),
     'expires'=>                   array('Expires',           'datetime',  ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_LIST, 6 ),
     'hidden'=>                    array('Hidden',            'bool',   0, AF_HIDE),
  
     'checkin'=>                   array('Checkin',           'datetime',   '', AF_OBLIGATORY|AF_LOG, 19),
     'checkout'=>                  array('Checkout',          'datetime',   '', AF_OBLIGATORY|AF_LOG, 19),
  
      // shift hours
     //'start_hour' =>                array('Start Time',        'str', '', AF_SEARCHABLE|AF_HIDE_LIST|AF_LOG, 5),
     //'end_hour' =>                  array('End Time',          'str', '', AF_SEARCHABLE|AF_HIDE_LIST|AF_LOG, 5),
  
     'num_months'=>                array('# Months',          'float',    0, AF_READONLY|AF_HIDE_LIST, '3.2'),
     'num_days'=>                  array('# Days',            'int',    0, AF_READONLY, 4),
     'num_hours'=>                 array('# Hours',           'float',    0, AF_HIDE_LIST|AF_READONLY, '2.2'),
     'num_guests'=>                array('# Guests',          'intSelect', 0, AF_LOG, array(1,8,1, '')),
      //'num_packages'=>              array('# Packages',         'float',    0, AF_HIDE_LIST|AF_READONLY, '4.2'),
                    
     //'package_unit'=>              array('Package Unit',    	 'many2one', 'EA', AF_HIDE_LIST|AF_READONLY, 'product_unit'),
     //'package_id' =>               array('Package',            'many2one', 0, AF_READONLY|AF_LOG|AF_SEARCHABLE, 'product', array('active' => 1, 'category_id' => PRODUCT_CATEGORY_PACKAGE), 'name'),
     //'catering_id' =>              array('Catering',           'many2one', 0, AF_READONLY|AF_LOG|AF_SEARCHABLE, 'product', array('active' => 1, 'category_id' => PRODUCT_CATEGORY_CATERING), 'name'),
  
     'user_id'=>                   array('Author',            'link',   ATT_DEFAULT_USER_ID, AF_HIDE_LIST|AF_SEARCHABLE|AF_READONLY, 'user'),
     'city_id'=>                   array('City',              'link',   0, AF_READONLY|AF_SEARCHABLE, 'geo_city'),
     'apt_id'=>                    array('Apartment',         'link',   0, AF_SEARCHABLE|AF_LOG, 'property'),
     'apartment_name'=>            array('Apartment Name',    'str',        '', AF_HIDE, 50),
     'city_name'=>                 array('City Name',         'str',        '', 0, 128),

     'guest_id'=>                  array('Guest ID',          'link',   0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),
     'host_id'=>                   array('Host',              'link',   0, AF_HIDE_ADD|AF_READONLY, 'user'),

      // 'traveler_id'=>               array('Old Guest ID',      'link',   ATT_DEFAULT_GUEST_ID, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'guest'),
     'org_id'=>                    array('Org',               'link',   ATT_DEFAULT_ORG_ID, AF_SEARCHABLE, 'org', '', 'org.org_name'),
     'contact_id'=>                array('Contact',    			  'link',   ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY_EDIT, 'contact'),
     'bill_to'=>                   array('Bill To',           'valSelect', 0, AF_SEARCHABLE, $billtoArray),
     
     'agent_id'=>                  array('Agent',             'link',   ATT_DEFAULT_AGENT_ID, AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'agent'),
     'agent_contact'=>             array('Agent Contact',     'link',   ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'contact'),
      
      //'cc_id'=>                     array('CC',                'link',       0, AF_HIDE, 'cc'), // last used cc
     'remote_ip'=>                 array('IP',                'ip',        ATT_DEFAULT_CLIENT_IP, AF_SEARCHABLE|AF_READONLY, 15 ),
     'remote_cc'=>                  array('Country Code',     'many2one', ATT_DEFAULT_CLIENT_CC, AF_HIDE_LIST, 'countries'),
     'legal_entity_id'=>           array('Legal Entity',      'many2one', ATT_DEFAULT_LEGAL_ID, AF_SEARCHABLE|AF_LOG, 'legal_entity'),
  
     'address_id'=>                array('Address',           'one2one',    0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'address'),
     'language'=>                   array('Language',          'many2one', ATT_DEFAULT_LANGUAGE, 0, 'language'),
  
     'arrival_method'=>            array('Arrive by',         'valSelect',    '', AF_HIDE_LIST|AF_LOG, $arrivalTypeArray),
     'arrival_from'=>              array('City of departure',  'str',    '', AF_HIDE_LIST|AF_LOG, 32),
     'arrival_number'=>            array('Flight/Train #',     'str',    '', AF_HIDE_LIST|AF_LOG, 50),
     'arrival_time'=>              array('Arrival airport/station',   'time',    ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_LOG),
     'arrival_property'=>          array('Arrival property',  'time',    ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_LOG),
     'arrival_notes'=>             array('Arrival notes',     'str',    '', AF_HIDE_LIST|AF_LOG, 100),
     'airport_pickup'=>            array('Pickup',            'bool',   0, AF_LOG, 30),
  
     //'pickup_location'=>           array('Pickup location',    'many2one', 0, AF_HIDE_LIST|AF_LOG, 'landmark', array('type' => LANDMARK_TYPE_BOARDING)), // for boats
     //'dropoff_location'=>           array('Dropoff location',   'many2one', 0, AF_HIDE_LIST|AF_LOG, 'landmark', array('type' => LANDMARK_TYPE_BOARDING)), // for boats
  
     'extra_info'=>                array('Guest notes',        'text',   '', AF_HIDE_LIST|AF_READONLY_EDIT|AF_HIDE_ADD),
     'message'=>                   array('Message to guest',  'text',   '', AF_HIDE_LIST),
     'alert'=>                     array('NB!',               'str',    '', AF_HIDE_LIST, 100),
     'notes'=>                     array('Our Notes',         'text',    '', AF_HIDE_LIST),
     'invoice_notes'=>             array('Invoice Notes',     'str',    '', AF_HIDE_LIST, 200),

     'cancel_reason'=>             array('Cancellation reason', 'text',    '', AF_HIDE_LIST),
     'cancel_user_id'=>            array('Canceled by',       'link',    ATT_DEFAULT_NULL, AF_HIDE_LIST, 'user'),
                          
     //'ref'=>                       array('Ref',               'str',    '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 20),
     //'ref_other'=>                 array('Ref (other)',       'str',    '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 20),
     //'ref_searchterm'=>            array('Searchterm',        'str',    '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 50),

     
     'currency'=>                  array('Currency',          'valSelect', 0, AF_HIDE_LIST|AF_LOG, $currencyArray),
     'rate_type'=>                 array('Rate Type',         'valSelect', 'day', AF_HIDE_LIST|AF_OBLIGATORY|AF_LOG, $rateTypeArray),

     'rate_class'=>                array('Rate Class',        'many2one', RATE_CLASS_STANDARD, AF_HIDE_LIST|AF_LOG, 'rate_class'),
     'rate_base'=>                 array('Base Rate',         'money',   0, AF_HIDE_LIST|AF_LOG),
     'rate_locked'=>               array('Lock Rate?',        'bool',  0, AF_HIDE_LIST),
     'rate_locked'=>               array('Lock Rate?',        'bool',  0, AF_HIDE_LIST),
     'invoice_locked'=>            array('Invoice locked?',   'bool',  0, AF_HIDE_LIST),
     'guest_registered'=>          array('Guest registered?', 'bool',  0, AF_HIDE_LIST),

     //'fee_locked'=>                array('Lock Fee?',         'bool',  0, AF_HIDE_LIST),
     'send_email'=>                array('Send email updates?', 'bool',  0, AF_HIDE_LIST),
     'monthly_billing'=>           array('Bill monthly?',   	'bool', 0, AF_HIDE_ADD|AF_HIDE_LIST),
     //'price_breakdown_id'=>        array('Price breakdown',   'link', 0, AF_HIDE_LIST|AF_LOG, 'price_breakdown'),

     'hourly'=>                    array('Hourly billing',    'bool', 0, 0), // redundant, but for simplicity
     'billing_period'=>            array('Billing period',    'many2one', BILLING_PERIOD_DAY, AF_OBLIGATORY, 'billing_period', array('active' => 1)),
     'invoice_contact'=>           array('Invoice Contact?',  'bool', 0, AF_HIDE_ADD|AF_HIDE_LIST),
  
     'discount'=>                  array('Base Discount',     'discount',  0, AF_HIDE_LIST|AF_LOG),
     //'discount_locked'=>           array('Lock Discount?',    'bool',  1, AF_HIDE_LIST),
  
     'total'=>                     array('Total',             'money',   0, AF_HIDE_LIST|AF_READONLY|AF_TOTAL|AF_LOG),
                                                                        
     'charge_city_tax' =>          array('Charge City Tax?' ,'bool', 0, AF_LOG, 0),
     'city_tax_rate' =>            array('City Tax Rate' ,   'surcharge', '', AF_LOG, 0),
     'charge_tax' =>               array('Charge V.A.T?'       ,'bool', 0, AF_LOG, 0),
     'tax_included' =>             array('Tax included?'       ,'bool', 1, AF_LOG, 0),
     
     'fee_service' =>              array('Service fee',       'money',   0, AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'fee_cleaning' =>             array('Cleaning fee',      'money',   0, AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'fee_local'    =>             array('Local fee',         'money',   0, AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'fee_booking'  =>             array('Booking fee',       'money',   0, AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'fee_other'    =>             array('Other fee',         'money',   0, AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'fee_pickup'   =>             array('Pickup fee',        'money',   0, AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     //'fee_callout'=>               array('Call-out fee',      'money',  0,  AF_HIDE_ADD|AF_HIDE_LIST, 8),
     //'fee_callout_quantity'=>      array('Call-out fee quantity', 'float',  0,  AF_HIDE_ADD|AF_HIDE_LIST, '3.2'),
     //'fee_waiting'=>               array('Waiting fee',       'money',  0,  AF_HIDE_ADD|AF_HIDE_LIST, 8),
     //'fee_waiting_quantity'=>      array('Waiting fee quantity',  'float',  0,  AF_HIDE_ADD|AF_HIDE_LIST, '3.2'),
  
     'fee_json'=>                  array('Fees',              'json',   0, AF_READONLY|AF_HIDE_LIST|AF_LOG),
     'fees'=>                      array('Total Fees',        'money',   0, AF_READONLY|AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'city_tax'=>                  array('City Tax',          'money',  0, AF_READONLY|AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'other_charges'=>             array('Other charges',     'money',   0, AF_HIDE_LIST|AF_READONLY|AF_LOG|AF_TOTAL),
     'grand_total'=>               array('Grand Total',       'money',   0, AF_HIDE_LIST|AF_READONLY|AF_LOG|AF_TOTAL),
  
     'deposit'=>                   array('Deposit',           'money',   0, AF_HIDE_LIST|AF_READONLY|AF_LOG),
     'deposit_percentage'=>        array('Deposit %',         'int',   0, AF_HIDE_LIST|AF_LOG, 2),
  
     'paid'=>                      array('Paid',              'money',   0, AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'authorized'=>                array('Authorized',        'money',   0, AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'balance'=>                   array('Balance',           'money',   0, AF_HIDE_LIST|AF_READONLY|AF_TOTAL),
     'commission'=>                array('Commisssion',       'commission',   0, AF_HIDE_LIST|AF_LOG|AF_TOTAL),
     'invoice'=>                   array('Invoices',     'one2many', 0, AF_HIDE_LIST|AF_READONLY, 'invoice', 'res_id'),
  
     'booking_id'=>                array('Booking ID',        'str',    '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD|AF_READONLY, 20),
     'booking_pin'=>               array('Booking PIN',       'str',    '', AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD|AF_READONLY, 10),
  
     //'feedback_sent'=>             array('Feedback request sent?', 'bool',  0, AF_READONLY|AF_HIDE_LIST),
     //'feedback_confirmed'=>        array('Feedback confirmed?', 'bool',  ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_LIST|AF_LOG),
     //'feedback_score'=>            array('Feedback score?',     'int',  ATT_DEFAULT_NULL, AF_READONLY|AF_LOG),
     //'review_confirmed'=>          array('Review confirmed?', 'bool',  ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_LIST|AF_LOG),

     'reminder_sent'=>             array('Reminder sent?',     'yesno',  0, AF_READONLY|AF_HIDE_LIST),
     'review_sent'=>               array('Review request sent?', 'yesno',  0, AF_READONLY|AF_HIDE_LIST),
     'review_score'=>              array('Review score?',     'int',  ATT_DEFAULT_NULL, AF_READONLY|AF_LOG),
     
     //'block_id'=>                  array('Block ID',    	     'link',     ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 'block'),
     //'block_parent'=>              array('Block Parent',    	 'link',     ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 'reservation'),

     'org_currency'=>              array('Original Currency',  'valSelect', 0, AF_HIDE_LIST, $currencyArray),
     'org_rate_type'=>             array('Original Rate Type', 'valSelect', 'day', AF_HIDE_LIST, $rateTypeArray),
     'org_rate_base'=>             array('Original Base Rate', 'money',   0, AF_HIDE_LIST),
     'org_fee_cleaning'=>          array('Original Cleaning Fee', 'money',   0, AF_HIDE_LIST),

     'chat_count'=>                array('Chat count',         'int', 0, AF_HIDE_ADD|AF_READONLY, 3),
     
     'decline_reason'=>            array('Declined reason',     'int',    '', AF_HIDE_LIST),
     'cancel_reason'=>             array('Cancellation reason', 'text',    '', AF_HIDE_LIST),
     'upload'                =>    array('Uploaded Documents',  'media',     '', 0, $reservation_media_options),

     /** one2many - not stored in table */
     'charge'=>                    array('Charges',           'one2many', 0, AF_HIDE_LIST|AF_READONLY, 'charge', 'res_id'),
     'payments'=>                  array('Payments',          'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'payment', 'res_id'),
     'transactions'=>              array('Transactions',      'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'transaction', 'res_id'),
     'withdrawals'=>               array('Withdrawals',       'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'withdrawal', 'res_id'),
     'changelog'=>                 array('Log',               'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_READONLY, 'changelog',  'parent_id', array('obj_type' => 'reservation')), // last is filter
     'chat'=>                      array('Correspondence',    'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_READONLY, 'chat',       'parent_id', array('parent_type' => 'reservation')),
     'maillog'=>                   array('All sent mails',    'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_READONLY, 'mail_queue', 'parent_id', array('parent_type' => 'reservation')), // last is filter
  ),
  
  
  
  // reservation exceptions
  "res_exception" => 
  
  array(
     'id'=>                        array('ID',                'id',         0, AF_PRIMARY|AF_AUTOINCREMENT),
     'active'                   => array('Active',            'bool',       1, AF_SEARCHABLE, 1),
     'created'=>                   array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD),
     'timestamp'=>                 array('Updated',           'timestamp',   ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD, 6 ),
     'user_id' =>                   array('Author',            'link',     ATT_DEFAULT_USER_ID, AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),
     //'author_id'=>                 array('Author',            'link',   ATT_DEFAULT_USER_ID, AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),
     'org_id' =>                   array('Organization',      'many2one',   ATT_DEFAULT_NULL, AF_SEARCHABLE, 'org', array('client_id' => $_SESSION['client_id'])),
                                                                            
  // which city/type/owner/apt (todo - make linked ajax choosers)                                
  
     'rank'=>                      array('Rank',              'int', 0, AF_HIDE_ADD, 3),

     'city_id' =>                  array('City',             'many2one',   0, AF_SEARCHABLE, 'geo_city', array('active' => 1), 'name'),
     'property_type'=>             array('Property Type',     'valSelect',  0, AF_OBLIGATORY, $propertyTypeArray),
//     'owner_id'=>                  array('Owner',             'link',   ATT_DEFAULT_NULL, AF_SEARCHABLE, 'owner', array('shortstay' => 1)),
     'host_id'=>                   array('Host',              'link',   ATT_DEFAULT_NULL, AF_HIDE_ADD|AF_READONLY, 'user'),
     'apt_id' =>                   array('Property',          'link',   ATT_DEFAULT_NULL, AF_SEARCHABLE, 'property'),

  //   'priority'                 => array('Priority'          ,'int', 0, 0, 6),
  
  // reservation parameters (input vars)
     'start'=>                     array('From Date',              'date',       ATT_DEFAULT_NULL, 0),
     'end'=>                       array('To Date',                'date',       ATT_DEFAULT_NULL, 0),

     'start_time'=>                array('From Time',              'time',       ATT_DEFAULT_NULL),
     'end_time'=>                  array('To Time',                'time',       ATT_DEFAULT_NULL),
//     'num_months'=>                array('# Months',          'float',      ATT_DEFAULT_NULL, 0, '3.2'),
     'num_days'=>                  array('# Days >=',         'int',        ATT_DEFAULT_NULL, 0),
     'num_hours'=>                 array('# Hours >=',        'float',      ATT_DEFAULT_NULL, 0, '2.2'),
     'num_guests'=>                array('# Guests ',         'intSelect',  ATT_DEFAULT_NULL, 0, array(1,8,1, '')),
  
  // calculated reservation parameters (input vars)
     //'fit_factor'=>                 array('Fit factor (>= 0-100%)', 'int', ATT_DEFAULT_NULL, 0),
     'fit_between'=>                array('Fit factor between (>= 0-100%)', 'int', ATT_DEFAULT_NULL, 0, 3),
     'fit_next_to'=>                array('Fit factor next to (>= 0-100%)', 'int', ATT_DEFAULT_NULL, 0, 3),
     'days_from_now'=>              array('# Days from now <=',     'int', ATT_DEFAULT_NULL, 0),
     'days_from_now_gt'=>           array('# Days from now >',      'int', ATT_DEFAULT_NULL, 0),
  
  // property exceptions (out vars) 
     'book_direct' =>              array('Book Direct?',       'yesno',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'max_guests'=>                array('Max guests',        'int',        ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'min_stay'=>                  array('Min stay',          'int',        ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'max_stay'=>                  array('Max stay',          'int',        ATT_DEFAULT_NULL, AF_SEARCHABLE),                                                                                
     'rate_day'=>                  array('Day rate',          'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_weekend'=>              array('Weekend rate',       'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
  //         'rate_hour'=>                 array('Hour rate',         'money',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_extraperson'=>          array('Rate Extra person', 'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_week'=>                 array('Week rate',          'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_2_weeks'=>              array('2-Week rate',          'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_3_weeks'=>              array('3-Week rate',          'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_month'=>                array('Month rate',          'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),

     'changeover'=>                array('Changeover',        'int',  0, 0),

     //   'discount'=>                  array('Discount',          'discount',   ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'surcharge'=>                 array('Surcharge',         'surcharge',  ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_change'=>               array('Rate Change',       'percent_or_number',  ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'last'=>                      array('Stop processing',    'bool',  0, AF_SEARCHABLE),  
     'description'=>               array('Description',        'str',    '', 0, 255),
   ),
  
  
    
  "property" => 
  
  array(
  
     'id'=>                        array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'type' =>                     array('Type',              'valSelect', '', AF_OBLIGATORY|AF_HIDE_EDIT, $propertyTypeArray),
//     'owner_id'=>                  array('Owner',             'link',   0, AF_SEARCHABLE|AF_OBLIGATORY|AF_INLINE_ADD, 'owner', array('active' => 1)),
     'site_id'=>                   array('Site',              'link',   ATT_DEFAULT_SITE_ID, 0, 'site'),
     'host_id'=>                   array('Host',              'link',   ATT_DEFAULT_USER_ID, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),
     'user_id'=>                   array('User',              'link',   ATT_DEFAULT_USER_ID, AF_SEARCHABLE, 'user'),
     'user_profile_id'=>           array('Profile',           'link',   ATT_DEFAULT_NULL, AF_SEARCHABLE, 'user_profile'),
  
     'client_id'=>              array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),
     'legal_entity_id'=>        array('Legal Entity',      'many2one', 0, AF_OBLIGATORY, 'legal_entity'),
     'parent_id'=>              array('Parent Property',  'link', ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE, 'property'),
     'is_parent'=>              array('Placeholder Property',  'bool', 0, 0),
     'pageviews'=>              array('Pageviews',         'int',  '', AF_SEARCHABLE, 10 ),

     'currency'=>             array('Currency',          'valSelect', 0, AF_HIDE_LIST|AF_LOG, $currencyArray),
     'gallery'              => array('Album size'       , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),
     //'media'                => array('Media'            , 'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'media', 'parent_id'),
     'media'                => array('Media',             'media',     '', 0, $property_media_options),
     'media_json'           => array('Media (json)',      'json',     ''),
     'changelog'            => array('Log',               'one2many', 0, AF_HIDE_ADD|AF_HIDE_LIST|AF_CASCADE_DELETE|AF_READONLY, 'changelog', 'parent_id'),
     'descriptions'         => array('Descriptions',    'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'property_description', 'property_id'),
  
     'fids'                     => array('Foreign IDs'       ,'json', '', AF_HIDE_LIST|AF_HIDE_ADD, 255),
     'guid'=>                      array('GUID',             'uuid',    ATT_DEFAULT_UUID, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 24),
     'priority'                 => array('Priority'          ,'int', 0, AF_HIDE, 8),
     'active'                   => array('Active'            ,'bool', 0, AF_SEARCHABLE, 1),
     'activation_timestamp'     => array('First Actived'     ,'str', '', 0, 20),
     'import_timestamp'         => array('Last Imported'     ,'str', '', 0, 20),
     
     'test'                     => array('Test Property?'    ,'bool', 0, AF_SEARCHABLE, 1),
     'processed'                => array('Processed'         ,'bool', 0, AF_HIDE, 1),
     'created'=>                   array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),
     'timestamp'=>                 array('Updated',           'timestamp',   ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 6 ),
     'scraped'=>                   array('Scraped',           'date',   '', AF_HIDE, 10 ),
     'source_id'                => array('Source'            ,'link', 0, AF_HIDE_LIST|AF_HIDE, 'source'),
     'source_url'               => array('Source URL'        ,'str', 1, AF_HIDE, 100),
     'dest_id'=>                   array('Destination',    	  'many2one', ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_LIST|AF_HIDE_ADD|AF_HIDE_EDIT, 'source'),
  
     'hide'=>                      array('Hide',              'bool', 0, AF_HIDE, ''),
     'hide_local'=>                array('Hide Locally',      'bool', 0, AF_HIDE, ''),
     'timezone' =>                  array('Timezone',         'timezone', '', 0, 32),
  
     'city_name'=>                 array('City Name',         'str',        '', 0, 128),
     'city_id'=>                   array('City where shown',  'many2one',   0, AF_OBLIGATORY|AF_SEARCHABLE|AF_READONLY_EDIT, 'geo_city', array('active' => 1), 'name'),
     //'borough_id' =>              array('District',          'many2one',   0, AF_SEARCHABLE|AF_HIDE_LIST|AF_HIDE_ADD, 'borough'),
     //'neighborhood_id' =>          array('Area',              'many2one',   0, AF_SEARCHABLE|AF_HIDE_LIST|AF_HIDE_ADD, 'neighborhood'),
  
     'name'=>                      array('Name',              'str',    '', AF_OBLIGATORY|AF_SEARCHABLE|AF_LOG, 50),
     'shortname'=>                 array('URL',               'str',    '', AF_OBLIGATORY|AF_HIDE_ADD|AF_HIDE_LIST, 30),
     'short_description'=>         array('Short Description', 'str',    '', AF_HIDE_LIST, 200),
     'special_deal'=>              array('Special Deal',      'text',    '', AF_HIDE_LIST),
     'quote'=>                     array('Quote',             'str',    '', AF_HIDE_LIST, 150),
  
     'input_lang'=>                array('Input language',    'valSelect', 'en', AF_OBLIGATORY|AF_HIDE_LIST|AF_HIDE, $langArray),
  
     'address_street'     => array('Street'            ,'str','', AF_HIDE_LIST|AF_SEARCHABLE, 100),
     'address_number'     => array('Street Number'     ,'str', '',  AF_HIDE_LIST, 12),
     'address_suffix'     => array('Suffix'            ,'str','', AF_HIDE_LIST, 10),
     'address_postcode'   => array('Postcode'          ,'str','', AF_HIDE_LIST|AF_SEARCHABLE, 10),
     'address_city'       => array('City (Address)'              ,'str','', AF_OBLIGATORY|AF_HIDE_LIST, 50),
     'address_state'    => array('State/Province/Region'      , 'str', '', AF_HIDE_LIST, 50),
     'address_country'    =>  array('Country',           'many2one', 0, AF_OBLIGATORY, 'countries'),
  
     'location_id'          => array('Location'         , 'link', 0, AF_READONLY_EDIT, 'landmark'),
     'location_accuracy'    => array('Accuracy'    			, 'map',  0, AF_HIDE_ADD|AF_HIDE_LIST),
     'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_bounds'      => array('Bounds'           , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
  
     'staff_notes' => array('Staff Notes',             'text',    '', AF_HIDE_LIST),
  
     'review_count'=>              array('Review Count',      'int',    0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST, 4),
     'review_score'=>              array('Review Score',      'float',  0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST, '4.2'),
     'review_recommend'=>          array('# Recommend',       'int',    0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST, 4),

     /** old */
     'review_nr'=>                 array('# Ratings',          'int',    0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST, ''),
  
  //         'external_account_number'     => array('Account #'          ,'str','', AF_HIDE_LIST, 10),
     'account_rent'       => array('Account rent'                ,'str','', AF_HIDE_LIST, 10),
     'account_lo_tax'     => array('Account lo tax'              ,'str','', AF_HIDE_LIST, 10),
     'account_hi_tax'     => array('Account hi tax'              ,'str','', AF_HIDE_LIST, 10),
     'account_no_tax'     => array('Account no tax'              ,'str','', AF_HIDE_LIST, 10),
     'account_city_tax'   => array('Account city tax'            ,'str','', AF_HIDE_LIST, 10),
     'account_booking_fee'=> array('Account booking fee'         ,'str','', AF_HIDE_LIST, 10),
  
     'golf_distance' =>     array('Golf Distance',               'int', '', AF_HIDE_LIST, 3),
     'data' =>              array('Other Data',                  'json', '', AF_HIDE_LIST),
     'distances' =>         array('Distances',                   'json', '', AF_HIDE_LIST),
     'amenities' =>         array('Amenities',                   'json', '', AF_HIDE_LIST),
     'children'=>                 array('Child Properties',   'one2many', ATT_DEFAULT_NULL, AF_HIDE_LIST, '__this->type', 'parent_id'),
     'calendar_availability'   => array('Cal. Availability',     'text', '', AF_HIDE_LIST),
     'calendar_startdate'      => array('Cal. start',              'date', '', AF_HIDE_LIST),
     'calendar_changeover'     => array('Cal. changeover',        'text', '', AF_HIDE_LIST),
     'calendar_minstay' => array('Cal. Min stay',              'text', '', AF_HIDE_LIST),

     'locked' => array('Locked (Readonly import)',              'json', '', AF_HIDE_LIST),
  ),
  
  
  
  // base class for rental property (boat, shortstay)
  "serviced_rental" => 
  //unset($base_fields['type']),
  array(
     'book_direct'=>               array('Directly bookable?', 'valSelect', 0, AF_HIDE_LIST, $yes_no_req),
  
     'rating'=>                    array('Rating',            'int',    0, AF_HIDE_LIST, ''),
  
      // checkin
     'checkin_from'=>              array('Checkin from',       'str',    0, AF_HIDE|AF_HIDE_LIST, 5),
     'checkin_to'=>                array('Checkin to',         'str',    0, AF_HIDE|AF_HIDE_LIST, 5),
     'checkout_from'=>             array('Checkout from',      'str',    0, AF_HIDE|AF_HIDE_LIST, 5),
     'checkout_to'=>               array('Checkout to',        'str',    0, AF_HIDE|AF_HIDE_LIST, 5),
  
     'cancellation_policy'=>       array('Cancellation Policy', 'many2one', 0, AF_HIDE|AF_HIDE_LIST, 'cancellation_policy'),

     'licensed' =>                 array('Licensed?'           ,'bool', 0, 0, 0),
     'charge_city_tax' =>          array('Charge City Tax?'    ,'bool', 0, AF_LOG, 0),
     'charge_tax' =>               array('Charge V.A.T?'       ,'bool', 0, AF_LOG, 0),
     'tax_included' =>             array('Tax included?'       ,'bool', 0, AF_LOG, 0),
  
      // deposit
     'deposit'=>                   array('Deposit %',         'int',    0, 0),
     'security_deposit'=>          array('Security Deposit',  'money',  0, AF_HIDE_LIST, 4),
  
  ),
  
  

  "shortstay" => 
  //unset($base_fields['id']),
  array(
     'id'=>                        array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'type' =>                     array('Type',              'valSelect', 'shortstay', AF_OBLIGATORY|AF_HIDE, $propertyTypeArray),
     'corporate'                => array('Corporate'          ,'bool', 0, AF_HIDE, 1),
     'licensed'                 => array('Licensed?'          ,'bool', 0, AF_HIDE_LIST, 1),
//     'owner_id'=>                  array('Owner',             'link',   0, AF_SEARCHABLE|AF_OBLIGATORY|AF_INLINE_ADD, 'owner', array('shortstay' => 1, 'active' => 1)),
  
     // day rate
     'rate_day'=>                  array('Day rate',          'int',  0, AF_SEARCHABLE|AF_LOG, 8),
     'rate_person'=>               array('Day rate per person', 'int',  0, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD|AF_LOG, 8),
     'rate_weekend'=>              array('Weekend rate',      'int',  0, AF_SEARCHABLE|AF_LOG, 8),
     'rate_week'=>                 array('Week rate',         'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_2_weeks'=>              array('2-Week rate',          'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_3_weeks'=>              array('3-Week rate',          'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'rate_month'=>                array('Month rate',        'int',      ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'weekend_rate_cutoff'=>       array('Weekend rate cutoff',  'int',  7, AF_SEARCHABLE|AF_LOG, 3),
     'max_guests'=>                array('Max guests',        'intSelect', 2, AF_OBLIGATORY|AF_SEARCHABLE|AF_LOG, array(1,10,1, '')),
     'rate_num_guests'=>           array('# Guests incl. in rate',  'int',  2, AF_HIDE_LIST|AF_LOG, 2),
  
     'rate_day_min'=>              array('Min. Day rate',     'int',  0, AF_HIDE_LIST|AF_LOG, 8),
     'rate_day_max'=>              array('Max. Day rate',     'int',  0, AF_HIDE_LIST|AF_LOG, 8),
     'rate_hour'=>                 array('Hour rate',          'int',  0, AF_LOG, 8),
  
     'min_stay'=>                  array('Min stay (days)',   'int',    3, AF_SEARCHABLE, 5),
     'max_stay'=>                  array('Max stay (days)',   'int',    0, AF_SEARCHABLE|AF_HIDE|AF_HIDE_LIST, 5),
                                                                 
     'rate_extraperson'=>          array('Extra person',      'int',  0, AF_SEARCHABLE|AF_LOG, 8),
     //'rate_shortstay'=>            array('Short stay',        'money',  0, AF_HIDE|AF_LOG, 8),
  
     // discounts
     //'discount'=>                  array('Flat Discount',     'discount',    0, AF_HIDE_LIST, 4),
     'rate_change'=>               array('Rate Change',       'percent_or_number',  ATT_DEFAULT_NULL, AF_SEARCHABLE),
     'discount_week'=>             array('Weekly Discount',   'int',  0, AF_SEARCHABLE),
     'discount_2_weeks'=>          array('2-Week Discount',   'int',  0, AF_SEARCHABLE),
     'discount_3_weeks'=>          array('3-Week Discount',   'int',  0, AF_SEARCHABLE),
     'discount_month'=>            array('Monthly Discount',   'int',  0, AF_SEARCHABLE),
  
     'changeover'=>                array('Changeover',        'int',  0, 0),
  
      // fees
     'fee_cleaning'=>              array('Cleaning fee',      'int',  0,  AF_HIDE_ADD|AF_HIDE_LIST, 8),
     
     'fee_local'=>                 array('Local fee',         'int',  0,  AF_HIDE_ADD|AF_HIDE_LIST, 8),
     'fee_pickup'=>                array('Pickup fee',        'int',  0,  AF_HIDE_ADD|AF_HIDE_LIST, 8),
     'fee_booking'=>               array('Booking fee',       'int',  0, AF_HIDE_ADD|AF_HIDE_LIST, 8),
     'fee_other'=>                 array('Other fees',        'int',  0,  AF_HIDE_ADD|AF_HIDE_LIST, 8),
  
     'num_toilets'        => array('# Toilets',      'intSelect', 0, 0, array(1,10,1, '')),
     'num_bedrooms'       => array('# Bedrooms',      'intSelect', 0, 0, array(1,10,1, '')),
     'num_bathrooms'      => array('# Bathrooms',      'intSelect', 0, 0, array(1,10,1, '')),
     'hosting_property_type'=>     array('Property Type',     'many2one',   0, AF_SEARCHABLE, 'hosting_property_type', array('active' => 1)),
     'hosting_room_type'=>         array('Room Type',         'many2one',   0, AF_SEARCHABLE, 'hosting_room_type', array('active' => 1)),

     'facilities'         => array('Facilities'        ,'msel','', AF_HIDE_LIST, 'facility', array('serviced' => 1)),
  
  ),
  


  "facility" => 
  
  array(
     'id'               => array('ID'             ,'id',   0, AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE),
     'name'             => array('Name'           ,'str', '', AF_SEARCHABLE|AF_OBLIGATORY, 100),
     'group_name'       => array('Group'          ,'str', '', AF_SEARCHABLE, 100),
     'searchable'       => array('Searchable'     ,'bool', 0, AF_SEARCHABLE),
     'serviced'         => array('Serviced'       ,'bool', 0, AF_SEARCHABLE),
     'golf'             => array('Golf Course'    ,'bool', 0, AF_SEARCHABLE),
     'golf_rental'      => array('Golf Rental'    ,'bool', 0, AF_SEARCHABLE),
  ),
  
  "cancellation_policy" => 
  array(
     'id'=>                  array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'name'               => array('Name',              'str',  0, AF_OBLIGATORY|AF_SEARCHABLE,8),
     'description'        => array('Description',       'html',  0, AF_OBLIGATORY|AF_SEARCHABLE,8),
//     'site_id'=>             array('Site',            'link',   ATT_DEFAULT_SITE_ID, 0, 'site'),
//     'client_id'=>           array('Client',    		  'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'lead_time'          => array('Lead Time (Days)'   ,'int', '', AF_HIDE|AF_READONLY, 2),         
     'refund'             => array('Refund (%)'         ,'int', '', AF_HIDE|AF_READONLY, 2),         

  ),

  "checkin_time" => 
  array(
     'id'=>                  array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'name'               => array('Name',              'str',  0, AF_OBLIGATORY|AF_SEARCHABLE,8),
  ),

  "checkout_time" => 
  array(
     'id'=>                  array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'name'               => array('Name',              'str',  0, AF_OBLIGATORY|AF_SEARCHABLE,8),
  ),
  
  "calendar_import" => 
  array(
     'id'=>                  array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'active'=>              array('Active?',           'bool', 1, AF_READONLY|AF_HIDE_ADD),
     'created'=>             array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),
     'last_sync'=>           array('Last Sync',         'datetime',   ATT_DEFAULT_NULL, AF_HIDE_ADD|AF_READONLY),
     'site_id'=>             array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_OBLIGATORY, 'site'),
     'client_id'=>           array('Client',    			  'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_HIDE_ADD|AF_SEARCHABLE|AF_READONLY_EDIT|AF_OBLIGATORY, 'client'),
     'source_id'=>           array('Source',    			  'many2one', ATT_DEFAULT_SOURCE_ID, AF_OBLIGATORY|AF_SEARCHABLE|AF_READONLY_EDIT, 'source'),
     'user_id'=>             array('User',              'link', ATT_DEFAULT_USER_ID, AF_HIDE_ADD|AF_READONLY|AF_OBLIGATORY, 'user'),
     'host_id'=>             array('Host',              'link', 0, AF_HIDE_ADD|AF_READONLY|AF_OBLIGATORY, 'user'),
     'property_type'=>       array('Property Type',     'valSelect', 0, AF_READONLY|AF_SEARCHABLE|AF_HIDE_ADD|AF_OBLIGATORY, $propertyTypeArray),
     'apt_id'=>              array('Property ID',       'link', 0, AF_HIDE_ADD|AF_READONLY, 'user'),
     'name'               => array('Name',              'str',  '', AF_SEARCHABLE|AF_OBLIGATORY,255),
     'fid'=>                 array('Foreign ID',        'str',  '', 0, 40),
     'fname'               => array('Foreign Name',     'str',  '', AF_SEARCHABLE,255),
     'url'                => array('URL',               'url',  '', AF_SEARCHABLE|AF_OBLIGATORY),
  ),

  
  "invoice" => 
  
  array(
     'id'=>                        array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'cc_id'=>                     array('CC',                'link',       0, AF_HIDE, 'cc'), // last used cc
     'res_id'=>                    array('Reservation ID',    'link', 0, AF_SEARCHABLE, 'reservation'),
     //'order_id'=>                  array('Order ID',          'link', 0, AF_SEARCHABLE, 'payment_order'),

     'parent_id'=>                 array('Parent Id',         'parent_id',   ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST, 11),
     'parent_type'=>               array('Parent Type',       'parent_type', ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST),

     'apt_id'=>                    array('Property',          'link', 0, AF_READONLY|AF_SEARCHABLE|AF_HIDE_ADD, 'property'),
     'property_type'=>             array('Property Type',     'valSelect', 0, AF_READONLY|AF_SEARCHABLE|AF_HIDE_ADD, $propertyTypeArray),
     'site_id'=>                   array('Site',              'many2one',   ATT_DEFAULT_SITE_ID, 0, 'site'),
     'city_id'=>                   array('City',              'link',   0, AF_READONLY|AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD, 'geo_city', array('active' => 1), 'name'),
//     'country_id'=>                array('Country',           'link',   0, AF_READONLY|AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD, 'country', array('active' => 1), 'name'),
//     'owner_id'=>                  array('Owner',             'link',   ATT_DEFAULT_OWNER_ID, AF_SEARCHABLE|AF_READONLY|AF_HIDE_EDIT|AF_HIDE_ADD, 'owner', array('shortstay' => 1), 'first_name'),
     'host_id'=>                   array('Host',              'link', 0, AF_HIDE_ADD|AF_READONLY, 'user'),
     'agent_id'=>                   array('Agent',             'link',       ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_HIDE|AF_READONLY, 'agent'),
     'legal_entity_id'=>           array('Legal Entity',      'many2one', 0, AF_SEARCHABLE|AF_LOG, 'legal_entity'),
     'client_id'=>                 array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'head_invoice'=>              array('Head invoice#',     'bool', 0, AF_READONLY),
     'locked'=>                    array('Locked?',           'bool', 0, AF_READONLY),
     'corporate'=>                 array('Corporate?',        'bool', 0, AF_READONLY),
     'due'=>                       array('Due',               'bool', 0, 0),
     'received'=>                  array('Received on',       'datetime', ATT_DEFAULT_NULL, AF_READONLY),
     'user_id'=>                   array('User ID',           'link', ATT_DEFAULT_USER_ID, AF_HIDE_ADD|AF_READONLY|AF_SEARCHABLE, 'user'),
     'guest_id'=>                  array('Guest ID',          'link', 0, AF_HIDE_ADD|AF_READONLY|AF_SEARCHABLE, 'user'),
  //         'legacy_id'=>                 array('Custom inv. ID',         	'str',   '', 0, 20),
     'guest_name'=>                array('Guest',         		'str',   '', AF_READONLY, 40),
     'org_id'=>                    array('Employer',          'many2one', 0, AF_SEARCHABLE, 'org',["active" => 1]),
     'contact_id'=>                array('Department',    	  'many2one',   ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_HIDE_ADD, 'contact', ["org_id" => "__this->org_id", "active" => 1]),
     'bill_to'=>                   array('Bill To',           'valSelect', 0, AF_SEARCHABLE, $billtoArray),
     'type'=>                      array('Type',              'many2one', 0, AF_READONLY_EDIT, 'inv_type'),
     'timestamp'=>                 array('Updated',           'timestamp',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),
     'status'=>                    array('Status',            'many2one', INV_STATUS_DRAFT, AF_SEARCHABLE|AF_LOG, 'inv_status'),
     'status_change_timestamp'=>   array('Status Changed on', 'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),
     'created'=>                   array('Created',           'datetime', ATT_DEFAULT_NOW, AF_READONLY|AF_HIDE_LIST),
     'invoice_date'=>              array('Invoice Date',      'date',   ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_LOG),
     'duedate'=>                   array('Due',               'date',   ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_LOG),
     'start_date'=>                array('From',              'datetime',   '', AF_LOG),
     'end_date'=>                  array('To',                'datetime',   '', AF_LOG),
     'sequence'=>                  array('Sequence #',        'int',    0, AF_READONLY|AF_HIDE_LIST),
  
     'booking_pin' =>              array('Booking PIN',       'str',    '',  AF_HIDE|AF_READONLY, 10),
  
     'invoice_id'=>                array('Invoice ID',        'str',    '', AF_SEARCHABLE|AF_LOG, 30),
     'invoice_id_required'=>       array('Invoice ID Required?', 'bool', 0, AF_HIDE_LIST|AF_READONLY),
     'concerning'=>                array('Concerning',        'str',    '', AF_HIDE_LIST, 200),
     'customer_notes'=>            array('Customer Notes',    'str',    '', AF_HIDE_LIST, 200),
     'location'=>                  array('Location',          'str',    '', AF_HIDE_LIST, 200),
     'notes'=>                     array('Notes',             'text',    '', AF_HIDE_LIST),
     'message'=>                   array('Message',           'text',    '', AF_HIDE_LIST),
  
     'sent_to'=>                   array('Sent to',           'str',    '', AF_HIDE_LIST|AF_LOG, 255),
     'sent_date'=>                 array('Sent Date',         'datetime',   ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_LOG),
  
     'export_timestamp'=>          array('Export timestamp',  'datetime',    ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_HIDE_ADD|AF_HIDE_EDIT|AF_READONLY|AF_LOG),
     'export_gateway'=>            array('Export gateway',    'str',    '', AF_HIDE_LIST|AF_HIDE_ADD|AF_LOG|AF_HIDE_EDIT|AF_READONLY, 20),
  
     'currency'=>                  array('Cur',               'valSelect', 0, AF_READONLY, $currencyArray),
     'shipping'=>                  array('Shipping',          'money',  0, AF_HIDE_LIST|AF_READONLY|AF_TOTAL),
     'handling'=>                  array('Handling',          'money',  0, AF_HIDE_LIST|AF_READONLY|AF_TOTAL),
  //         'discount'=>                  array('Discount',          'discount',  0, AF_HIDE_LIST),
     'tax'=>                       array('Tax',               'money',  0, AF_HIDE_LIST|AF_READONLY|AF_TOTAL),
     'tax_of_which'=>              array('Of which tax',      'money',  0, AF_HIDE_ADD|AF_LOG|AF_READONLY),
     'amount'=>                    array('Amount',            'money',  0, AF_READONLY|AF_TOTAL),
     'subtotal'=>                  array('Subtotal',          'money',  0, AF_HIDE_ADD|AF_READONLY),
     'total'=>                     array('Total',             'money',  0, AF_READONLY|AF_TOTAL),
     'paid'=>                      array('Paid',              'money',  0, AF_READONLY|AF_TOTAL|AF_LOG),
     'balance'=>                   array('Balance',           'money',  0, AF_READONLY|AF_TOTAL),
     'pending'=>                   array('Pending Payments',  'money',  0, AF_READONLY|AF_TOTAL|AF_LOG),
     'authorized'=>                array('Authorized Payments', 'money',  0, AF_READONLY|AF_TOTAL|AF_LOG),

     'lineitems'=>                 array('# Lines',           'int',    0, AF_READONLY|AF_HIDE_LIST),
     'paid_date'=>                 array('Paid date',         'datetime',   '', AF_READONLY|AF_HIDE_LIST),
     'address_id'=>                array('Billing Address',   'one2one',    0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'address'),
     'inv_lineitems'=>             array('Lineitems',         'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'inv_lineitem', 'inv_id'),
                                
     'charge_city_tax' =>          array('Charge City Tax?' ,'bool', 0, AF_LOG, 0),
     'charge_tax' =>               array('Charge V.A.T?'       ,'bool', 0, AF_LOG, 0),
     'tax_included' =>             array('Tax included?'       ,'bool', 0, AF_LOG, 0),
  
  //         'block_id'=>                  array('Block ID',           'str',      ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 13),
     'block_id'=>                  array('Block ID',    	     'link',     ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 'block'),
     'block_parent'=>              array('Block Parent',    	 'link',     ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 'invoice'),
  
     'processed'                => array('Processed'         ,'bool', 0, AF_HIDE),
  
     'payments'     =>             array('Payments',       'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'payment', 'inv_id'),
     'withdrawals'  =>             array('Withdrawals',    'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'withdrawal', 'inv_id'),      
  ),
  
  
  "inv_lineitem" => 
  
  array(                    
     'id'=>                        array('ID',                'id',        0, AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE),
     'inv_id'=>                    array('InvID',             'parent_id', 0, AF_HIDE|AF_OBLIGATORY, 'invoice'),
     'user_id'=>                   array('User',              'link',      ATT_DEFAULT_USER_ID, AF_HIDE_ADD|AF_READONLY, 'user'),
     'product_id'=>                array('Product',           'many2one',  ATT_DEFAULT_NULL, 0, 'product'),
     'variant_id'=>                array('Variant ID',    		'link',      0, 0, 'product_variant'),
     'supplier_id'=>               array('Supplier',          'many2one',  0, AF_HIDE, 'supplier'),
     'type'=>                      array('Type',              'many2one',  0, 1, 'lineitem_type'),
     'timestamp'=>                 array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY, 6 ),
     'created'=>                   array('Created',           'date',       ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_READONLY),
     'item_number'=>               array('Item number',       'str',       '', AF_HIDE_ADD|AF_READONLY, 40),
     'quantity'=>                  array('Quantity',          'float',     1, 1, '2.4'),
     'currency'=>                  array('Currency',          'valSelect', 0, 1, $currencyArray),
     'amount'=>                    array('Unit price',        'money',     0, AF_LOG),
     'discount'=>                  array('Discount',          'discount',  0, AF_LOG),
     'subtotal'=>                  array('Subtotal',          'money',     0, AF_HIDE_ADD|AF_READONLY),
     'tax_category'=>              array('Tax Category',      'many2one',  0, AF_OBLIGATORY, 'tax_category', array('active' => 1)),
     'tax_percentage'=>            array('Tax %',             'float',     0, AF_LOG, '2.2'),
     'tax_of_which'=>              array('Of which tax',      'money',     0, AF_HIDE_ADD|AF_LOG|AF_READONLY),
     'tax'=>                       array('Tax (added)',       'money',     0, AF_HIDE_ADD|AF_LOG|AF_READONLY),
     'shipping'=>                  array('Shipping',          'money',     0, 0),
     'handling'=>                  array('Handling',          'money',     0, 0),
     'total'=>                     array('Total',             'money',     0, AF_HIDE_ADD|AF_LOG|AF_READONLY),
     'description'=>               array('Description',       'text',  '', 0, 255),
     'account_number' =>           array('Account #',         'str',   '', AF_HIDE_LIST, 20),
  
  //         'block_id'=>                  array('Block ID',           'str',      ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 13),
     'block_id'=>                  array('Block ID',    	     'link',     ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 'block'),
     'block_parent'=>              array('Block Parent',    	 'link',     ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 'invoice'),         
  ),
  
  
  "charge" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'status'=>            array('Status',            'int',   0, 0, 4 ),
     'user'=>              array('User',              'int',   ATT_DEFAULT_USER_ID, 0, 6 ),
     'ipn_id'=>            array('IPN',               'int',   0, 0, 6 ),
     'cc_id'=>             array('CC ID',             'link',  1, AF_OBLIGATORY|AF_READONLY, 'cc'),
     'inv_id'=>            array('InvID',             'link', 0, AF_OBLIGATORY|AF_READONLY|AF_SEARCHABLE, 'invoice'),
     'res_id'=>            array('ResId',             'link',  1, AF_OBLIGATORY|AF_READONLY|AF_SEARCHABLE, 'reservation'),
     'timestamp'=>         array('Timestamp',         'timestamp',  ATT_DEFAULT_NOW, 0, 6 ),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_READONLY),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
  
     'paymentaction'=>     array('Action',            'str',  '', AF_HIDE_LIST, 20 ),
     'acct'=>              array('Acct',              'str',  '', AF_HIDE_LIST, 20 ),
     'currency'    =>      array('Currency',          'valSelect', 0, 0, $currencyArray),
     'amount'=>            array('Amount',            'money', 0, 1),
     'description'=>       array('Desc',              'str',  '', AF_HIDE_LIST, 100 ),
     'remote_timestamp'=>  array('RTimeS',            'str',  '', AF_HIDE_LIST, 20 ),
     'correlationid'=>     array('CorId',             'str',  '', AF_HIDE_LIST, 20 ),
     'ack'=>               array('Ack',               'str',  '', 0, 10 ),
     'version'=>           array('Version',           'str',  '', AF_HIDE_LIST, 10 ),
     'build'=>             array('Build',             'str',  '', AF_HIDE_LIST, 10 ),
     'avscode'=>           array('AVS OK',            'str',  '', AF_HIDE_LIST, 2 ),
     'cvv2match'=>         array('CVV OK',            'str',  '', AF_HIDE_LIST, 2 ),
     'transactionid'=>     array('TX ID',             'str',  '', 0,  20 ),
     'amt'=>               array('Amt',               'money', 0, AF_HIDE_LIST),
     'payment_error'=>     array('Error',             'text',  '', AF_HIDE_LIST),
  ),
  
  
  "gateway" => 
  
  array(
     'id'               => array('ID'             ,'id',   0, AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE),
     'name'             => array('Name'           ,'str', '', AF_SEARCHABLE|AF_OBLIGATORY, 50),
  
     'username'         => array('UserName'      ,'str', '', 0, 100),
     'password'         => array('Password'      ,'str', '', 0, 100),
     'signature'        => array('Signature'     ,'str', '', 0, 200),
     'endpoint'         => array('Endpoint'      ,'str', '', 0, 200),
  
     'test_username'         => array('Tetst UserName'      ,'str', '', 0, 100),
     'test_password'         => array('Tetst Password'      ,'str', '', 0, 100),
     'test_signature'        => array('Tetst Signature'     ,'str', '', 0, 200),
     'test_endpoint'         => array('Tetst Endpoint'      ,'str', '', 0, 200),
  
  ),
  
  
  "transaction" => 
  // for testing
  // $inv_id = 2679;
  // $pay_id = 1145;
  // $res_id = 35195;
  
  array(
     'tx_id'=>             array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     //'tx_st'=>             array('User level',        'many2one', 0, 'tx_st'),
     'cc_id'=>             array('CC ID',             'link',  ATT_DEFAULT_NULL, AF_READONLY_EDIT, 'cc'),
     'inv_id'=>            array('InvID',             'link',  ATT_DEFAULT_NULL, AF_READONLY_EDIT, 'invoice'),
     'res_id'=>            array('ResId',             'link',  ATT_DEFAULT_NULL, AF_READONLY_EDIT, 'reservation'),
     // 'order_id'=>          array('Order',    			    'link',  ATT_DEFAULT_NULL, AF_READONLY, 'payment_order'),
     'payment_id'=>        array('PaymentId',         'link',  ATT_DEFAULT_NULL, AF_READONLY_EDIT, 'payment'),
//     'owner_id'=>          array('OwnerId',           'link',  ATT_DEFAULT_NULL, AF_READONLY_EDIT, 'owner'),
     'host_id'=>           array('Host',              'link',  ATT_DEFAULT_NULL, AF_HIDE_ADD|AF_READONLY, 'user'),
     'client_id'=>         array('Client',    			  'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>           array('Site',    			    'link', ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE, 'site'),
  
     'tx_st'=>               array('TxSt',              'many2one', '', AF_SEARCHABLE, 'tx_status' ),
     'timestamp'=>           array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_READONLY),
     'tx_gateway'=>          array('Gateway',           'str',      '', AF_SEARCHABLE, 10 ),
     'tx_type'=>             array('TX Type',           'str',      '', AF_SEARCHABLE, 40 ),
     'ipn_test'=>            array('Test',              'bool',     0, 0),
     'txn_res'=>             array('TxnRes',            'str',      '', AF_SEARCHABLE, 10 ),
     'txn_id'=>              array('TxnId',             'str',      '', AF_SEARCHABLE, 50 ),
     'parent_txn_id'=>       array('Parent TxnId',      'str',      '', AF_SEARCHABLE, 50 ),
     'item_name'=>           array('Item Name',         'str',      '', AF_SEARCHABLE, 255),
     'item_number'=>         array('Item Number',       'str',      '', AF_SEARCHABLE, 20 ),
     'payment_date'=>        array('Date',              'str',      '', AF_SEARCHABLE, 22 ),
  
     'payment_status'=>    array('Payment Status',    'many2one', 0, AF_READONLY_EDIT, 'payment_status'),
     'pending_reason'=>    array('Pending Reason',    'str',    ATT_DEFAULT_NULL, AF_READONLY, 20),
     'reason_code'=>       array('Reason Code',       'str',    ATT_DEFAULT_NULL, AF_READONLY, 30),
  
     'payer_email'=>       array('Sender',          'str',    '', AF_SEARCHABLE, 20 ),
     'receiver_email'=>    array('Received',        'str',      '', AF_SEARCHABLE, 20 ),
  
     'memo'=>                array('Memo',             'str',      '', AF_SEARCHABLE|AF_HIDE_LIST, 255 ),
     'tx_notes'=>            array('Notes',           'str',      '', AF_SEARCHABLE, 4 ),
  
     'mc_gross'=>        array('Gross',                 'str',      '', AF_SEARCHABLE, 22 ),
     'mc_currency'=>     array('Currency',              'str',      '', AF_SEARCHABLE, 22 ),
     'mc_fee'=>          array('Fee',                   'str',      '', AF_SEARCHABLE, 22 ),
  
     'settle_currency'=>     array('Settle Currency',     'str',      '', AF_SEARCHABLE, 3 ),
     'settle_amount'=>       array('Settle Amount',       'str',      '', AF_SEARCHABLE, 22 ),
     'exchange_rate'=>       array('Exchange rate',       'str',      '', AF_SEARCHABLE, 22 ),
     
  
     'auth_id'=>         array('Auth ID',              'str',      '', AF_HIDE_LIST|AF_SEARCHABLE, 20),
     'auth_amount'=>     array('Auth Amount',          'str',      '', AF_HIDE_LIST|AF_SEARCHABLE, 20),
     'auth_exp'=>        array('Auth Expiration',      'str',      '', AF_HIDE_LIST|AF_SEARCHABLE, 25),
  
     'first_name'=>        array('First Name',      'str',      '', AF_HIDE_LIST|AF_SEARCHABLE, 50),
     'last_name'=>         array('Last Name',       'str',      '', AF_HIDE_LIST|AF_SEARCHABLE, 50),
     'residence_country'=> array('Country',         'str',      '', AF_HIDE_LIST|AF_SEARCHABLE, 2),

     'refund_amount'=>     array('Refund Amount',    'money', 0, AF_SEARCHABLE),
     'bank_id'=>          array('Bank ID',              'str',      '', AF_SEARCHABLE, 10 ),
      'bank_name'=> array('Bank name', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'bank_account'=> array('Bank account', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'transfer_reference'=> array('Transfer reference', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'consumer_name'=> array('Consumer name', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'consumer_account'=> array('Consumer account', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'consumer_bic'=> array('Consumer bic', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'bitcoin_address'=> array('Bitcoin address', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'bitcoin_amount'=> array('Bitcoin amount', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'bitcoin_rate'=> array('Bitcoin rate', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'bitcoin_uri'=> array('Bitcoin uri', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'paypal_reference'=> array('Paypal reference', 'str', '', AF_HIDE_LIST|AF_SEARCHABLE, 128),
      'amount_remaining'=> array('Amount remaining', 'money', 0, AF_HIDE_LIST|AF_SEARCHABLE),
  ),
  
  
  "payment_type" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>              array('Name',              'str',   '', 1, 20 ),
     'user_select'=>       array('Selectable source?',  'bool', 0, AF_READONLY|AF_HIDE_ADD),
     'refundable'=>        array('Refundable?',  'bool', 0, AF_READONLY|AF_HIDE_ADD),
  ),
  
  
  "payment_source" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>              array('Name',              'str',   '', 1, 20 ),
     'description'=>       array('Description',       'str',   '', 1, 200 ),
  ),
  
  
  "payment_status" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>              array('Name',              'str',   '', 1, 20 ),
  ),
  
  
  "withdrawal" => 
  array(
     'id'=>                array('ID',                'id',   0,    AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE, 14 ),
     'created'=>           array('Date',              'datetime',   ATT_DEFAULT_NOW, AF_READONLY),
     'payment_id'=>        array('Payment',           'link',       ATT_DEFAULT_NULL, AF_SEARCHABLE, 'payment'),
//     'owner_id'=>          array('Owner',             'link',       ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY, 'owner'),
     'recipient_id'=>      array('Recipient',         'link', 0, AF_HIDE_ADD|AF_READONLY, 'user'),
     'host_id'=>           array('Host',              'link',       ATT_DEFAULT_NULL, AF_HIDE_ADD|AF_READONLY, 'user'),
     'agent_id'=>          array('Agent',             'link',       ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_HIDE|AF_READONLY, 'agent'),
     'client_id'=>         array('Client',    			  'many2one',   ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'gateway_id'=>        array('Gateway',           'many2one',   ATT_DEFAULT_NULL, AF_OBLIGATORY, 'gateway'),
     'inv_id'=>            array('InvID',             'link',       ATT_DEFAULT_NULL, AF_SEARCHABLE, 'invoice'),
     'res_id'=>            array('ResId',             'link',       ATT_DEFAULT_NULL, AF_SEARCHABLE, 'reservation'),
     'tx_id'=>             array('Our TXID',          'link',       ATT_DEFAULT_NULL, 0, 'transaction'),
  
     'payment_type'=>      array('Payment Method',    'many2one',   0, AF_READONLY_EDIT, 'payment_type'),
     'currency'=>          array('Currency',          'valSelect',  0, AF_READONLY|AF_OBLIGATORY, $currencyArray),
     'gross'=>             array('Amount',            'money',      0, AF_READONLY|AF_OBLIGATORY|AF_TOTAL),
     'fee'=>               array('Fee',               'money',      0, AF_READONLY|AF_OBLIGATORY|AF_TOTAL),
     'correction'=>        array('Correction',        'money',      0, AF_READONLY),
     'net'=>               array('Net',               'money',      0, AF_READONLY|AF_OBLIGATORY|AF_TOTAL),
     'notes'=>             array('Notes',             'str',        '', AF_HIDE_LIST, 255),
     'invoices'=>          array('Invoices',          'text',        '', AF_HIDE_LIST, 255),
     'recipient'=>         array('Recipient',         'str',        '', AF_OBLIGATORY, 255),
  
     'gateway_fee'=>       array('Gatweay Fee',         'money',    ATT_DEFAULT_NULL, AF_HIDE|AF_TOTAL),
     'gateway_ts'=>        array('Gatweay Timestamp',   'str',      ATT_DEFAULT_NULL, AF_READONLY, 30),
     'txn_id'=>            array('Gateway TXID',        'str',      ATT_DEFAULT_NULL, AF_READONLY|AF_SEARCHABLE, 50),
  
     'payments'=>          array('Payments',          'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'payment', 'withdrawal_id'),
  
  ),
  
  
  "payment" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'parent_id'=>         array('Parent Payment',    'link',   0, AF_SEARCHABLE, 'payment'),
     'client_id'=>         array('Client',    			  'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>           array('Site',    			    'link', ATT_DEFAULT_SITE_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'site'),
     'legal_entity_id'=>   array('Legal Entity',      'link', ATT_DEFAULT_LEGAL_ID, AF_SEARCHABLE|AF_LOG, 'legal_entity'),
     'timestamp'=>         array('Timestamp',         'timestamp',  ATT_DEFAULT_NOW, AF_HIDE, 14 ),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_SEARCHABLE|AF_READONLY),
     'payment_date'=>      array('Paid Date',         'datetime',  ATT_DEFAULT_NOW, AF_SEARCHABLE|AF_READONLY),
     'tx_id'=>             array('Our TXID',           'link', 0, 0, 'transaction'),
     'inv_id'=>            array('InvID',             'link', 0, 0, 'invoice'),
     'res_id'=>            array('ResId',             'link',  0, AF_SEARCHABLE, 'reservation'),
     'org_id'=>            array('OrgId',             'link',  0, AF_SEARCHABLE, 'org'),
     // 'order_id'=>          array('Order',    			    'link', ATT_DEFAULT_NULL, AF_READONLY, 'payment_order'),
     'user_id'=>           array('Author',            'link',   ATT_DEFAULT_USER_ID, AF_HIDE_LIST|AF_SEARCHABLE|AF_READONLY, 'user'),
//     'from_owner_id'=>     array('From Owner',        'link',  0, AF_SEARCHABLE|AF_READONLY_EDIT, 'owner'),
//     'owner_id'=>          array('Owner',             'link',  0, AF_SEARCHABLE|AF_READONLY_EDIT, 'owner'),
     'sender_id'=>         array('Sender',            'many2one', 0, 0, 'user'),
     'recipient_id'=>      array('Recipient',         'many2one', 0, 0, 'user'),
     'host_id'=>           array('Host',              'link', 0, AF_HIDE_ADD|AF_READONLY, 'user'),
     'guest_id'=>          array('Guest',             'link',   ATT_DEFAULT_NULL, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST|AF_SEARCHABLE, 'user'),
     'agent_id'=>          array('Agent',             'link',  ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY_EDIT, 'agent'),
     'cc_id'=>             array('CC ID',             'link',  0, AF_SEARCHABLE, 'cc'),
     'charge_id'=>         array('Charge',            'link',  0, AF_SEARCHABLE, 'charge'),
     'gateway_id'=>        array('Gateway',           'many2one', 0, AF_SEARCHABLE, 'gateway'),
     'remote_ip'=>         array('IP',                'ip',   ATT_DEFAULT_CLIENT_IP, AF_READONLY|AF_SEARCHABLE, 15 ),
  
     'verified'=>          array('Verified?',         'bool', 0, AF_READONLY),
     'txn_id'=>            array('Gateway TXID',      'str',  '', AF_READONLY|AF_SEARCHABLE, 30),

     'show_invoice'=>      array('Show on invoice?',  'bool', 1, AF_HIDE_ADD),
     'payment_type'=>      array('Payment Method',    'many2one', 0, AF_SEARCHABLE|AF_READONLY_EDIT, 'payment_type'),
     'payment_source'=>    array('Payment Source',    'many2one', PAYMENT_SOURCE_GUEST, AF_SEARCHABLE|AF_READONLY_EDIT, 'payment_source'),
     'source_id'=>         array('Source ID',         'int', ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY_EDIT), // really a link to agent/guest/org/owner/client etc..
  
     'currency'=>          array('Currency',          'valSelect', 0, AF_OBLIGATORY, $currencyArray),
     'amount'=>            array('Amount',            'money', 0, AF_OBLIGATORY|AF_TOTAL),
     'amount_remaining'=>  array('Amount remaining',  'money', 0, AF_HIDE_LIST|AF_SEARCHABLE),
     'description'=>       array('Desc',              'str',  '', AF_HIDE_LIST, 255),
  //         'transaction_id'=>    array('Tx ID',            'link',  1, AF_SEARCHABLE|AF_HIDE, 'transaction'),
  
     'payment_currency'=>  array('Pay Cur',           'str',    ATT_DEFAULT_NULL, AF_READONLY, 3),
     'payment_gross'=>     array('Gross',             'money',  ATT_DEFAULT_NULL, AF_READONLY|AF_TOTAL, 'payment_currency'),
     'payment_fee'=>       array('Fee',               'money',  ATT_DEFAULT_NULL, AF_READONLY|AF_TOTAL, 'payment_currency'),
     'payment_net'=>       array('Net',               'money',  ATT_DEFAULT_NULL, AF_READONLY|AF_TOTAL, 'payment_currency'),
     'payment_notes'=>     array('Notes',             'str',    ATT_DEFAULT_NULL, AF_HIDE_LIST, 255 ),
  
     'settle_currency'=>   array('Rcv Cur',           'str',    ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY, 3),
     'settle_amount'=>     array('Rcvd',              'money',  ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_TOTAL),
     'exchange_rate'=>     array('Rate',              'float',  ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY, '6.6'),
  
     'payment_status'=>    array('Payment Status',    'many2one', 0, AF_SEARCHABLE|AF_READONLY_EDIT, 'payment_status'),
     'pending_reason'=>    array('Pending Reason',    'str',    ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY, 20),
     'reason_code'=>       array('Reason Code',       'str',    ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY, 30),
  
     'withdrawal_id'=>        array('Withdrawal ID',                'link',     ATT_DEFAULT_NULL, AF_READONLY, 'withdrawal'),
     'withdrawal_date'=>      array('Withdrawal Date',              'datetime', ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),
     'withdrawal_recipient'=> array('Withdrawal Recipient',         'str',      ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY, 100),
     'withdrawal_currency'=>  array('Withdrawal Currency',          'str',      ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY, 3),
     'withdrawal_amount'=>    array('Withdrawal Amount',            'money',    ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_TOTAL),
     'withdrawal_fee'=>       array('Withdrawal Fee',               'money',    ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),
     'withdrawal_type'=>      array('Withdrawal Payment Method',    'many2one', ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY, 'payment_type'),
     'withdrawal_tx_id'=>     array('Withdrawal TXID',              'link',     ATT_DEFAULT_NULL, AF_READONLY, 'transaction'),
  
     'withdrawals'=>       array('Withdrawals',       'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'withdrawal', 'payment_id'),
  
  //         'block_id'=>                  array('Block ID',           'str',      ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 13),
     'block_id'=>                  array('Block ID',    	     'link',     ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 'block'),
     'block_parent'=>              array('Block Inv ID',    	 'link',     ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 'invoice'),         
  
     'inv_lineitem_list'    =>  array('Lineitem list',    	   'str',     '', AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD|AF_HIDE_EDIT, 255),
  ),
  

  
  "weblog" => 
  array(                                           
     'id'=>                array('ID',                'id',   0,   AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'timestamp'=>         array('Timestamp',         'timestamp',      ATT_DEFAULT_NOW, AF_SEARCHABLE, 14 ),
     'city_id'=>           array('City',              'many2one',  ATT_DEFAULT_CITY_ID, AF_SEARCHABLE, 'geo_city'),
     'geo_id'=>            array('GeoObj',            'many2one',  ATT_DEFAULT_GEO_ID, 0, 'geoname'),
     'page'=>              array('Page',              'many2one',  ATT_DEFAULT_PAGE_ID, AF_SEARCHABLE, 'site_page'),
     'remote_ip'=>         array('IP',                'ip',        ATT_DEFAULT_CLIENT_IP, AF_READONLY|AF_SEARCHABLE, 15 ),
     'session_id'=>        array('Session ID',        'str',       ATT_DEFAULT_SESS_ID, AF_SEARCHABLE, 32 ),
     'country_code'=>      array('Country',           'str',       ATT_DEFAULT_CLIENT_CC, AF_SEARCHABLE, 2),
     'language'=>          array('Language',          'str',       ATT_DEFAULT_LANG, AF_SEARCHABLE, 2),
     'site_id'=>           array('Site ID',           'int',       ATT_DEFAULT_SITE_ID, AF_SEARCHABLE, 10 ),
//     'aff_id'=>            array('Aff. ID',           'int',       ATT_DEFAULT_AFF_ID, AF_SEARCHABLE, 10 ),
     'user_id'=>           array('User ID',           'int',       ATT_DEFAULT_USER_ID, AF_SEARCHABLE, 10 ),
     'property_id'=>       array('Property ID',       'int',       ATT_DEFAULT_PROPERTY_ID, AF_SEARCHABLE, 10 ),
     'property_type'=>     array('Property type',     'many2one',  ATT_DEFAULT_PROPERTY_TYPE, AF_SEARCHABLE, 'property_type'),
//     'owner_id'=>          array('Owner ID',           'int',       0, AF_SEARCHABLE, 10 ),
     'host_id'=>           array('Host ID',           'link',   0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),
  
  
  //         'remote_host'=>       array('Remote Host',       'str',  '', AF_SEARCHABLE, 50 ),
  //         'referer'=>           array('Referer',           'str',  '', AF_SEARCHABLE, 10 ),
  //         'pageviews'=>         array('Pageviews',         'int',  '', AF_SEARCHABLE, 10 ),
  //         'datetime'=>              array('Time (secs)',       'int',  '', AF_SEARCHABLE, 10 ),
  ),
  
  
  "address" => 
  
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE),
     'salutation'=>        array('Salutation',        'valSelect', '', 0, $salutationArray),
     'first_name'=>        array('First Name',        'str',    '', AF_SEARCHABLE, 50),
     'infix'=>             array('Infix',             'str',    '', AF_SEARCHABLE, 20),
     'last_name'=>         array('Last Name',         'str',    '', AF_SEARCHABLE, 50),
     'email_address'=>     array('Email',             'email',  '', AF_SEARCHABLE|AF_HIDE_LIST, 128),
     'organization'=>      array('Company/Dept.',     'str',    '', AF_SEARCHABLE, 200),
     'title'=>             array('Title/Attn',        'str',    '', AF_HIDE_LIST, 50),
     'address1'=>          array('Address1',          'str',    '', AF_HIDE_LIST, 50),
     'address2'=>          array('Address2',          'str',    '', AF_HIDE_LIST, 50),
     'city'=>              array('City',              'str',    '', AF_HIDE_LIST, 50),
     'state'=>             array('State',             'str',    '', AF_HIDE_LIST, 50),
     'zip'=>               array('Postal code',       'str',    '', AF_HIDE_LIST, 10),
     'country'=>           array('Country',           'many2one', ATT_DEFAULT_COUNTRY, AF_SEARCHABLE|AF_FORCE_SELECT, 'countries'),
     'home_phone'=>        array('Home Phone',        'phone',  '', AF_HIDE_LIST, 20),
     'work_phone'=>        array('Work Phone',        'phone',  '', AF_HIDE_LIST, 20),
     'cell_phone'=>        array('Cell Phone',        'phone',  '', AF_HIDE_LIST, 20),
     'phone1'=>            array('Phone',             'phone',  '', AF_HIDE_LIST, 20),
     'phone1_type'=>       array('Phone Type',        'many2one',  0, AF_HIDE_LIST, 'phone_type'),
     'phone2'=>            array('Phone2',            'phone',  '', AF_HIDE_LIST, 20),
     'phone2_type'=>       array('Phone2 Type',       'many2one',  0, AF_HIDE_LIST, 'phone_type'),
     'phone3'=>            array('Phone3',            'phone',  '', AF_HIDE_LIST, 20),
     'phone3_type'=>       array('Phone3 Type',       'many2one',  0, AF_HIDE_LIST, 'phone_type'),
     'fax'=>               array('Fax',               'phone',  '', AF_HIDE_LIST, 20),
     'web_address'=>       array('Web',               'url',    '', AF_HIDE_LIST, 50),

     'facebook'=>          array('Facebook',          'url',    '', AF_HIDE_LIST, 255),
     'twitter'=>           array('Twitter',           'str',    '', AF_HIDE_LIST, 255),
     'address_formatted'=> array('Formatted Address', 'text',   '', AF_HIDE_LIST),

     'address_type'=>      array('Address type',    	'many2one',   ADDRESS_TYPE_PHYSICAL, AF_HIDE_LIST, 'address_type'),
     'address_parent_id'=>         array('Parent Id',         'parent_id',   ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST, 11),
     'address_parent_type'=>       array('Parent Type',       'parent_type', ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST),
  
  ),
  
  "user" => 
  array(
     'id'=>                array('ID',                'id',         0,   AF_PRIMARY|AF_AUTOINCREMENT),
     'created'=>           array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY),
     'last_login'=>        array('Last login',        'datetime',   ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_HIDE_ADD|AF_HIDE_EDIT|AF_READONLY),
     'active'=>            array('Active?',           'bool', 1, AF_READONLY|AF_HIDE_ADD),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>           array('Site',    			    'many2one', ATT_DEFAULT_SITE_ID, AF_HIDE_ADD|AF_SEARCHABLE|AF_READONLY_EDIT, 'site'),
     'auth_sites'=>        array('Allowed Sites',     'msel',     '', 0, 'site', array('active' => 1)),
     'profile_id'=>        array('Profile',    			  'one2one', 0,   AF_HIDE_LIST|AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user_profile'),
     'verified'=>          array('Verified?',         'bool', 1, AF_READONLY|AF_HIDE_ADD),
     'user_level'=>        array('Type',              'many2one',   USER_LEVEL_USER,   AF_HIDE_ADD|AF_HIDE_LIST|AF_READONLY|AF_OBLIGATORY, "user_level"),
     'roles'=>             array('Roles',             'flags', 1, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD, $__USER_ROLES),
     'username'=>          array('Username',          'str', '',    AF_UNIQUE|AF_OBLIGATORY|AF_SEARCHABLE, 50),
     'password'=>          array('Password',          'str',   '',  AF_HIDE, 32),
     'auto_password'=>     array('Generated password?', 'bool', 0, AF_READONLY|AF_HIDE_ADD),
  ),
  
  
  "lead" => 
  
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'created'=>           array('Created',           'date',   ATT_DEFAULT_NOW, AF_READONLY|AF_HIDE_LIST),
     'timestamp'=>         array('Updated',           'timestamp',   ATT_DEFAULT_NOW, AF_READONLY|AF_HIDE_LIST, 6 ),
     'user_id'=>           array('Author',            'many2one',   ATT_DEFAULT_USER_ID, AF_HIDE_LIST|AF_SEARCHABLE|AF_READONLY, 'user'),
     'site_id'=>           array('Site',              'many2one',   ATT_DEFAULT_SITE_ID, AF_HIDE_LIST|AF_LOG, 'site'),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'status'=>            array('Status',            'many2one', '',  AF_SEARCHABLE, 'contact_status'),
     'contacted'=>         array('Contacted',         'date',     '', AF_SEARCHABLE|AF_HIDE_LIST),
  
     'salutation'=>        array('Salutation',        'valSelect', '', AF_HIDE_LIST, $salutationArray),
     'first_name'=>        array('First Name',        'str',    '', AF_SEARCHABLE, 50),
     'infix'=>             array('Infix',             'str',    '', AF_SEARCHABLE, 20),
     'last_name'=>         array('Last Name',         'str',    '', AF_SEARCHABLE, 50),
     'email_address'=>     array('Email',             'email',  '', AF_SEARCHABLE, 50),
     'org_id'=>            array('Org ID',            'many2one', 0, AF_HIDE_LIST, 'org'),
     'organization'=>      array('Organization',      'str',    '', AF_SEARCHABLE, 50),
     'department'=>        array('Department',        'str',    '', 0, 50),
     'title'=>             array('Title',             'str',    '', 0, 30),
     'address1'=>          array('Address1',          'str',    '', AF_HIDE_LIST, 50),
     'address2'=>          array('Address2',          'str',    '', AF_HIDE_LIST, 50),
     'city'=>              array('City',              'str',    '', AF_HIDE_LIST, 30),
     'state'=>             array('State/Province',    'str',    '', AF_HIDE_LIST, 30),
     'zip'=>               array('Postal code',       'str',    '', AF_HIDE_LIST, 10),
     'country'=>           array('Country',           'many2one', 0, AF_SEARCHABLE, 'countries'),
     'home_phone'=>        array('Home Phone',        'phone',  '', AF_HIDE_LIST, 20),
     'work_phone'=>        array('Work Phone',        'phone',  '', AF_HIDE_LIST, 20),
     'cell_phone'=>        array('Cell Phone',        'phone',  '', 0, 20),
     'fax'=>               array('Fax',               'phone',  '', AF_HIDE_LIST, 20),
     'web_address'=>       array('Web',               'url',    '', AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'notes'=>             array('Notes',             'text',    '', AF_HIDE_LIST),

     'gender'           => array('gender'       ,      'many2one', '', 0, 'gender'),
     'age'              => array('age',                'int',      '', 0 ),
     
     'salutation2'=>        array('Contact 2 - Salutation',        'valSelect', '', AF_HIDE_LIST, $salutationArray),
     'first_name2'=>        array('Contact 2 - First Name',        'str',    '', AF_HIDE_LIST|AF_SEARCHABLE, 50),
     'last_name2'=>         array('Contact 2 - Last Name',         'str',    '', AF_HIDE_LIST|AF_SEARCHABLE, 50),
     'department2'=>        array('Contact 2 - Department',        'str',    '', AF_HIDE_LIST, 50),
     'title2'=>             array('Contact 2 - Title',             'str',    '', AF_HIDE_LIST, 30),
     'email_address2'=>     array('Contact 2 - Email',             'email',  '', AF_HIDE_LIST, 50),
     'phone2'=>             array('Contact 2 - Phone',             'phone',  '', AF_HIDE_LIST, 20),
  
     'response'=>            array('Response',               'text',     '',  AF_SEARCHABLE|AF_HIDE_LIST),
     'last_guest'=>          array('Last guest',             'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 100),
     'last_guest_checkout'=> array('Last guest checkout',    'date',     '',  AF_SEARCHABLE|AF_HIDE_LIST),
     'contact_lead'=>        array('Contact lead',           'str',      '',  AF_SEARCHABLE, 100),
  
  ),
  
  
  
  
  "org" => 
  
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'active'=>            array('Active',            'bool',   1, AF_HIDE_ADD),
     'org_name'=>          array('Organization Name',  'str', '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
     'invoice'=>           array('Pay by invoice?',   'bool', 0, AF_HIDE_LIST),
     'monthly_billing'=>   array('Bill monthly?',   	'bool', 0, AF_HIDE_LIST),
     'address_id'=>        array('Address',           'one2one',    0,   AF_HIDE_LIST|AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'address'),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_HIDE_ADD|AF_SEARCHABLE|AF_READONLY_EDIT, 'client'),
  
     'export_timestamp'=>          array('Export timestamp',  'datetime',    ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_HIDE_ADD|AF_HIDE_EDIT|AF_READONLY|AF_LOG),
     'export_gateway'=>            array('Export gateway',    'str',    '', AF_HIDE_LIST|AF_HIDE_ADD|AF_LOG|AF_HIDE_EDIT|AF_READONLY, 20),
  
     'default_address'=>     array('Default Address',    	  'many2one', ADDRESS_TYPE_PHYSICAL, AF_OBLIGATORY|AF_HIDE_LIST, 'address_type'),
     'comment' =>        	   array('Comment',        			  'text',     '',  AF_HIDE_LIST),
     'coc_number'=>          array('Chamber of Commerce #', 'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'coc_city'=>            array('Ch. of Com. City',      'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'tax_number'=>          array('Tax number',            'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'bank_name'=>           array('Bank name',             'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'bank_city'=>           array('Bank city',             'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'bank_account_number'=> array('Bank Acct. #',          'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 30),
  //         'bank_branch_id'=>      array('Bank branch',         'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 100),
     'bank_iban_number'=>    array('Bank IBAN #',           'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 30),          
     'bank_routing_number'=> array('Bank Routing #',        'str',      '',  AF_SEARCHABLE|AF_HIDE_LIST, 20),
  
  //         'addresses'=>           array('Address List',          'one2many', 0, AF_HIDE_LIST, 'address', 'parent_id', "parent_type='org'"),
     'addresses'=>           array('Address List',          'one2many', 0, AF_HIDE_LIST, 'address', 'address_parent_id', array('address_parent_type' => 'org')),
     'contacts' =>           array('Contacts',              'one2many', 0, AF_HIDE_LIST, 'contact', 'org_id'),
                                                                                                          
  ),
  
  
  "contact_status" =>
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
  ),

  "contact" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY, 6 ),
     'modified'=>          array('Modified',          'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
  //         'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 50 ),
     'client_id'=>         array('Client',    			  'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'site_id' =>          array('Site',              'link', ATT_DEFAULT_SITE_ID, AF_OBLIGATORY, 'site'),
     'org_id'=>            array('Organization',      'link',  ATT_DEFAULT_NULL, AF_SEARCHABLE, 'org'),                               
     'agent_id'=>          array('Agent',             'link',  ATT_DEFAULT_NULL, AF_SEARCHABLE, 'agent'),                               
     'address_id'=>        array('Address',           'one2one',    0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'address'), // |AF_ONE2ONE_INTEGRATE
     'language'=>          array('Language',    			'many2one', 'en', AF_OBLIGATORY|AF_SEARCHABLE, 'language'),                               
  
     ),
  
  
  "product" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY, 6 ),
     'modified'=>          array('Modified',          'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, AF_HIDE_ADD),
     'source_type'=>       array('Source Type',       'str',  '', AF_HIDE, 50),
     'fid'=>               array('Foreign ID',        'str',  '', AF_SEARCHABLE, 20),
     'client_id'=>         array('Client',    			  'link', ATT_DEFAULT_CLIENT_ID, AF_HIDE_LIST|AF_OBLIGATORY|AF_SEARCHABLE, 'client'),
     'category_id'=>       array('Category',    		  'many2one', 0, AF_OBLIGATORY|AF_SEARCHABLE, 'product_category'),
  //         'language'=>          array('Language',    			'many2one', 'en', AF_OBLIGATORY|AF_SEARCHABLE, 'language'),                               
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100 ),
     'description'=>       array('Description',       'text',  '', AF_HIDE_LIST),
     'comment'=>           array('Comment',           'str',   '', AF_HIDE_LIST, 255),
     'unit'=>              array('Unit',    		      'many2one', 'EA', AF_OBLIGATORY, 'product_unit'),
     'currency' =>         array('Currency',          'valSelect', 'EUR', AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST, $currencyArray),
     'price'=>             array('Price',             'money',   0, 0),
     'minimum_quantity'=>  array('Min. Quantity',     'int',   0, 0),
     'cost_price'=>        array('Cost Price',        'money',   0, 0),
  //         'tax_percentage'=>    array('Tax Percentage',    'float', 0, 0, '2.2'),
     'tax_category'=>      array('Tax Category',      'many2one',  0, AF_OBLIGATORY, 'tax_category', array('active' => 1)),
     'tax_included'=>      array('Tax Included?',     'bool', 1, 0),
     'image' =>            array('Image',             'image', '', AF_HIDE_LIST, 128),
     'media' =>            array('Media',             'media', '', AF_HIDE_LIST, $product_media_options),
     'num_hours'=>         array('#Hours (packages)', 'float', 0, 0, '2.2'),
//     'stock'=>             array('Stock',             'float', 0, 0, '2.2'),
     ),
  
  "product_variant" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY, 6 ),
     'modified'=>          array('Modified',          'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'product_id'=>        array('Product ID',    		'link', ATT_DEFAULT_NULL, AF_OBLIGATORY, 'product'),
     'name'=>              array('Name',              'str', ATT_DEFAULT_NULL, AF_OBLIGATORY, 100),
     'option_id'=>         array('Option ID',    	    'link', ATT_DEFAULT_NULL, AF_OBLIGATORY, 'product_option'),
     'option_name'=>       array('Option Name',       'str', ATT_DEFAULT_NULL, AF_OBLIGATORY, 100),
     'option_value'=>      array('Option Value',      'str', ATT_DEFAULT_NULL, AF_OBLIGATORY, 50),
     'price'=>             array('Price',             'money',   0, 0),
     'stock'=>             array('Stock',             'float', 0, 0, '2.2'),
     ),
     
  "product_option" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 50 ),
     'description'=>       array('Description',       'text',   '', AF_HIDE_LIST),
     'values'=>            array('Values',            'text',   '', AF_HIDE_LIST),
     ),
    
  "product_category" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY, 6 ),
     'modified'=>          array('Modified',          'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY, 'client'),
     'language'=>          array('Language',    			'many2one', 'en', AF_OBLIGATORY|AF_SEARCHABLE, 'language'),                               
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 50 ),
     'description'=>       array('Description',       'text',   '', AF_HIDE_LIST),
     'comment'=>           array('Comment',           'str',   '', AF_HIDE_LIST, 255),
     'unit'=>              array('Default Unit',              'str',   '', AF_HIDE_LIST, 10),
     'tax_percentage'=>    array('Default Tax Percentage',    'float',   0, 0),
     'tax_category'=>      array('Default Tax Category',      'many2one',  0, 0, 'tax_category'),
     'tax_included'=>      array('Default Tax Included?',     'bool',    0, 0),
     ),
  
  
  "product_unit" => 
  array(
     'code'=>              array('Code',              'str',   0, AF_PRIMARY, 2),
     'active'=>            array('Active',            'bool',   1, 0),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 50 ),
     ),
  
  "product_supplier_map" => 
  array(
     'product_id'=>       array('Product',            'many2one',  0, AF_OBLIGATORY, 'product'),
     'supplier_id'=>      array('Supplier',           'many2one',  0, AF_OBLIGATORY, 'supplier'),
     ),
  
  "user_map" => 
  array(
     'id'=>            array('ID',             'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'created'=>       array('Created',        'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY),
     'verified'=>      array('Verified',       'bool',  0, 0),
     'site_id'=>       array('Site ID',        'link',  0, AF_OBLIGATORY, 'site'),
     'user_id'=>       array('User',           'link',  0, AF_OBLIGATORY, 'user'),
     'host_user_id'=>  array('Host',           'link',  0, AF_OBLIGATORY, 'user'),
     'permissions' =>  array('Permissions',    'json', '', 0),
     ),               

  "auth_log" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE|AF_READONLY, 14 ),
     //'expires'=>           array('Expires',           'datetime',   ATT_DEFAULT_NULL, AF_HIDE|AF_READONLY, 14 ),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'user_id' =>          array('User ID',           'link', ATT_DEFAULT_USER_ID, 0, 'user'),     
     'provider_id' =>      array('Provider ID',       'link', 0, 0, 'provider'),     
     'username' =>         array('Username',          'str', ATT_DEFAULT_USERNAME, 0, 50),     
     'user_level' =>       array('User Level',        'link', ATT_DEFAULT_USER_LEVEL, 0, 'user'),     
     'status' =>           array('Status',            'int', 0, 0),     
     'display_name' =>     array('Display Name',      'str', ATT_DEFAULT_DISPLAY_NAME, 0, 128 ),
     'remote_ip'=>         array('IP',                'ip',  ATT_DEFAULT_CLIENT_IP, AF_HIDE_LIST|AF_SEARCHABLE|AF_READONLY, 20),
     'remote_cc'=>         array('CC',                'many2one', ATT_DEFAULT_CLIENT_CC, AF_HIDE_LIST, 'countries'),
     'remote_city'=>       array('City',              'str', ATT_DEFAULT_CLIENT_CITY, AF_HIDE_LIST, 64),
     'remote_continent'=>  array('City',              'str', ATT_DEFAULT_CLIENT_CONTINENT, AF_HIDE_LIST, 2),
     'remote_location'=>   array('City',              'str', ATT_DEFAULT_CLIENT_LOCATION, AF_HIDE_LIST, 128),
     'remote_agent'=>      array('User Agent',        'str', ATT_DEFAULT_USER_AGENT, AF_HIDE_LIST),
     'message' =>          array('Message',           'str', '', 0, 255 ),
     
     'session_id'     => array('Session ID',          'str', ATT_DEFAULT_SESS_ID, 0, 128 ),
     'auth_token'     => array('Auth Token',          'str', '', 0, 128 ),
     
  ),

  "mail_log" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE|AF_READONLY, 14 ),

     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'user_id' =>          array('User ID',           'link', ATT_DEFAULT_USER_ID, 0, 'user'),     
     'mail_id' =>          array('Mail ID'  ,         'link', 0, AF_OBLIGATORY, 'mail_queue'),     
     'receiver_id' =>      array('Receiver ID',       'link', 0, 0, 'user'),     
     
     /** not yet impl */
     'campaign_id' =>      array('Mail Campaign ID',  'link', 0, 0, 'mail_campaign'),     

     'mail_guid'=>       array('GUID',             'str', '', 24),

     'remote_ip'=>         array('IP',                'ip',  ATT_DEFAULT_CLIENT_IP, AF_HIDE_LIST|AF_SEARCHABLE|AF_READONLY, 20),
     'remote_cc'=>         array('CC',                'link', ATT_DEFAULT_CLIENT_CC, AF_HIDE_LIST, 'countries'),
     'remote_city'=>       array('City',              'str', ATT_DEFAULT_CLIENT_CITY, AF_HIDE_LIST, 64),
     'remote_continent'=>  array('City',              'str', ATT_DEFAULT_CLIENT_CONTINENT, AF_HIDE_LIST, 2),
     'remote_location'=>   array('City',              'str', ATT_DEFAULT_CLIENT_LOCATION, AF_HIDE_LIST, 128),
     'remote_agent'=>      array('User Agent',        'str', ATT_DEFAULT_USER_AGENT, AF_HIDE_LIST, 128),
     'remote_referer'=>      array('Referer',         'str', ATT_DEFAULT_USER_AGENT, AF_HIDE_LIST, 128),

     'data'             => array('data',              'json',     '', AF_HIDE_ADD),
     
  ),

  "wishlist" => 
  array(
     'id'=>            array('ID',             'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'created'=>       array('Created',        'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY, 6 ),
     'site_id'=>       array('Product',        'link',  0, AF_OBLIGATORY, 'site'),
     'user_id'=>       array('User',           'link',  0, AF_OBLIGATORY, 'user'),
     'obj_type'=>      array('Object ID',      'str',  0, AF_OBLIGATORY, 128),
     'obj_id'=>        array('Object ID',      'int',  0, AF_OBLIGATORY),
     'name'=>          array('Name',           'str',  '', 0, 128 ),
     'description'=>   array('Descriptions',   'html', '', AF_HIDE_LIST),
     
     ),               

  "price_breakdown" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE|AF_READONLY, 14 ),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),
     'res_id' =>           array('Site',              'link', ATT_DEFAULT_SITE_ID, AF_OBLIGATORY, 'reservation'),
     'apt_id' =>           array('Property',          'link', ATT_DEFAULT_USER_ID, 0, 'property'),     
     'currency' =>         array('Currency',          'valSelect', 'EUR', AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST, $currencyArray),
     'city_tax'=>          array('City Tax',          'money',  0, AF_READONLY),     
     'fees'=>              array('Fees',              'money',  0, AF_READONLY),     
     'total'=>             array('Total',             'money',  0, AF_READONLY),     
     'average'=>           array('Averate',           'money',  0, AF_READONLY),     
     'count'=>             array('Item count',        'int',  0, AF_READONLY),     
     'discount'=>          array('Discount',          'discount', '', AF_HIDE_LIST|AF_LOG),
     'reason'=>            array('Reason',            'str',  '', 0, 200),
     'exceptions'=>        array('Exceptions',        'str',  '', 0, 200),
     'weekend_pricing'=>   array('Weekend pricing',   'bool', 0, 0),
     'checkin'=>           array('Checkin',           'date',   '', AF_HIDE_LIST, 50),
     'num_days'=>          array('# Days',            'int',  0, AF_READONLY, 3),
     'num_guests'=>        array('# Guests',          'int',   0, AF_READONLY, 3),
     'base_rate'=>         array('Base rate',         'money',   0, AF_HIDE_LIST|AF_READONLY),
     'base_rate_weekend'=> array('Base rate weekend', 'money',   0, AF_HIDE_LIST|AF_READONLY),
     'rate_type'=>         array('Rate Type',         'valSelect', 'day', AF_HIDE_LIST|AF_LOG, $rateTypeArray),
     'rate_class'=>        array('Rate Class',        'many2one', RATE_CLASS_STANDARD, AF_HIDE_LIST|AF_LOG, 'rate_class'),
     'rows'  =>            array('Rows',              'one2many', 0, AF_HIDE_LIST|AF_READONLY|AF_CASCADE_DELETE|AF_HIDE_ADD, 'price_breakdown_row', 'price_breakdown_id'),     
     ),
  
  "price_breakdown_row" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'price_breakdown_id'=>array('Parent ID',         'parent_id',  0, AF_OBLIGATORY, 'price_breakdown'),
     'weekend_rate'=>      array('Weekend rate',      'bool', 0, 0),
     'weekday'=>           array('Weekday',    			  'many2one', 0, AF_OBLIGATORY, 'weekday'),
     'date'=>              array('Date',              'date',  0, AF_OBLIGATORY),
     'currency' =>         array('Currency',          'valSelect', 'EUR', AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST, $currencyArray),
     'base_rate'=>         array('Base rate',         'money',   0, 0),
     'rate_change'=>       array('Rate change',       'percent_or_number', 0, 0),
     'rate'=>              array('Rate',              'money',   0, 0),
     'comment'=>           array('Comment',           'str',  '', 0, 200),
     ),  

  "supplier" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY, 6 ),
     'modified'=>          array('Modified',          'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),
     'address_id'=>        array('Address',           'one2one',    0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'address'), // |AF_ONE2ONE_INTEGRATE
     'language'=>          array('Language',    			'many2one', 'en', AF_OBLIGATORY|AF_SEARCHABLE, 'language'),                               
     'delivery'=>          array('Delivery?',         'bool',   0, 1),
  
     ),
  
  "tax_category" => 
  array(
     'code'=>              array('Code',              'str',   0, AF_PRIMARY, 2),
     'active'=>            array('Active',            'bool',   1, 0),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 50 ),
     'percentage'=>        array('Percentage',        'float',   0, 0, '2.2'),
     'country_code'=>      array('Country code',      'str',     0, 0, '2'),
     ),

  

  
  
  "agent" => 
  array(
     'id'=>                   array('ID',                'id',       0, AF_PRIMARY|AF_AUTOINCREMENT),
//     'parent_id'=>            array('User',              'one2one',  0, AF_OBLIGATORY|AF_HIDE_LIST|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user'),
     'active'=>            array('Active',            'bool',   1, 0),
     'name'=>                 array('Agent Name',        'str',      '', AF_OBLIGATORY|AF_LOG, 30),
     'address_id'=>           array('Address',           'one2one',    0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'address'), // |AF_ONE2ONE_INTEGRATE
     'client_id'=>            array('Client',    		  	 'link',       ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),

     'invoice'=>              array('Pay by invoice?',   'bool', 0, AF_HIDE_LIST),
     
//     'type'=>                 array('Agent Type',        'many2one', '', 0, 'agent_type'),
//     'languages'=>          array('Languages',         'json',     '', 0, 'language'),
     'custom_filters'=>       array('Custom Filters',    'text',   '', AF_HIDE|AF_HIDE_LIST|AF_HIDE_ADD, 0),
     'commission'=>           array('Standard Commisssion', 'commission', '', AF_READONLY|AF_HIDE_ADD|AF_LOG),
     'commission_charged'=>   array('Commission charged by agent?', 'bool', 0, AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST|AF_LOG),
     'balance_charged'=>      array('Balance charged by agent?', 'bool', 0, AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST|AF_LOG),
     'currency' =>            array('Currency',          'valSelect', 'EUR', AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST, $currencyArray),
     'booking_fee'=>          array('Booking Fee',       'money',   0, AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST),
     'send_feedback'=>        array('Send feedback request to guests from this agent?', 'bool', 0, AF_READONLY|AF_HIDE_ADD|AF_HIDE_LIST|AF_LOG),
     'logo' =>                array('Logo',                 'image',      '', AF_HIDE_LIST, 128),
  
     'partner_agent_id'=>    array('Partner Agent',         'link', 0, AF_HIDE, 'agent'),
     'contacts' =>           array('Contacts',              'one2many', 0, AF_HIDE_LIST, 'contact', 'agent_id'),
  //         'booking_fee'=>        array('Standard Commisssion', 'commission',   0, AF_HIDE_LIST|AF_LOG),
  
  ),
  
/**

  "affiliate" => 
  array(
     'id'=>                 array('ID',                  'id',       0, AF_PRIMARY|AF_AUTOINCREMENT),
     'created'=>            array('Created',             'datetime',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>          array('Timestamp',           'timestamp',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
     'active'  =>           array('Active?',             'bool', 1, AF_HIDE_ADD, 0),
  
//     'parent_id'=>          array('User',               'one2one',  0, AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user'),
     'name'=>               array('Name',               'str',      '', AF_OBLIGATORY, 100),
  
     'site_id'=>           array('Site',              'many2one',  ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD, 'site'),
     //'config_id'=>         array('Config',            'one2one', 0, AF_HIDE_LIST|AF_ONE2ONE_INTEGRATE, 'site_config'),
     //'scheme_id'=>         array('Scheme',            'one2one', 0, AF_HIDE_LIST|AF_ONE2ONE_INTEGRATE, 'site_scheme'),
     //'dim_id'=>            array('Dimensions',        'one2one', 0, AF_HIDE_LIST|AF_ONE2ONE_INTEGRATE, 'site_dim'),
  
     'live'=>                 array('Live?',              'bool',     0, 0),
     'commission'=>           array('Commission %',       'float',    0, AF_HIDE_LIST, '2.2'),
     'affiliate_script'=>     array('Script',             'str',      '', AF_HIDE_LIST, 100),
     'affiliate_dir'=>        array('Directory',          'str',      '', AF_HIDE_LIST, 50),
     'affiliate_css'=>        array('CSS',                'str',      '', AF_HIDE_LIST, 50),
     'affiliate_desc'=>      array('Description',        'text',     '', AF_HIDE_LIST),
  
  ),
  
  
  "owner" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
  
     'shortstay'=>         array('Shortstay?',        'bool', 1, AF_HIDE_ADD|AF_READONLY|AF_SEARCHABLE),
     
     'paypal_id_private'         => array('Paypal ID'      ,   'email',  '', AF_HIDE_ADD|AF_HIDE_LIST, 50),
     'paypal_id_usd'             => array('Paypal ID (for USD)',   'email',  '', AF_HIDE_ADD|AF_HIDE_LIST, 80),
     'payment_frequency'         => array('Paypal Payment Frequency',  'valSelect', 'monthly', AF_HIDE_ADD|AF_READONLY|AF_OBLIGATORY, $frequencyArray),
     'system_commission'         => array('System Commisssion', 'commission', '5%', AF_HIDE_ADD|AF_READONLY|AF_LOG|AF_HIDE),
     'parent_id'=>         array('User',              'one2one', 0, AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user'),
    
     'sms_alert'=>            array('SMS alert?',           'flags', '', AF_HIDE_LIST, $sms_flags),
  
  ),
  
  
  "guest" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'parent_id'=>         array('User',              'one2one', 0, AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user'),
     'org_id'=>            array('Org',               'many2one', ATT_DEFAULT_NULL, AF_HIDE, 'org'),
     'keep_payment_info'=> array('Remember Credit Card?', 'bool',   0, AF_HIDE_ADD),
     'notes' =>        		 array('Notes',        			'text',   '', AF_HIDE_ADD|AF_HIDE_LIST),
  //         'cc_id'=>             array('Credit Cards',      'link', 0, AF_HIDE_LIST|AF_CASCADE_DELETE, 'cc', 'guest_id'),
  ),
  

  "staff" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'parent_id'=>         array('User',              'one2one', 0, AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user'),
  //         'languages'=>         array('Languages',         'msel',     '', AF_HIDE_LIST, 'language'),
     'custom_filters'=>    array('Custom Filters',    'text',   '', AF_HIDE_LIST|AF_HIDE_ADD, 0),
  ),
  
  
  "admin" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'parent_id'=>         array('User',              'one2one', 0, AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user'),
     'custom_filters'=>    array('Custom Filters',    'text',   '', AF_HIDE_LIST|AF_HIDE_ADD, 0),
  ),

  "translator" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'parent_id'=>         array('User',              'one2one', 0, AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user'),
  //         'language'=>          array('Language',          'many2one', '', 1, 'language'),
  ),
  
  
  "contractor" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'parent_id'=>         array('User',              'one2one', 0, AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user'),
     'type'=>              array('Contractor Type',   'many2one', '', 0, 'contractor_type'),
     'event_types'=>       array('Event Types',       'msel',   '', 0, 'event_type', 0, 'name'),
     'custom_filters'=>    array('Custom Filters',    'text',   '', AF_HIDE_LIST|AF_HIDE_ADD, 0),
  //         'language'=>          array('Language',          'many2one', 'en', 0, 'language'),
  ),
  
  
  
  
  "system" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'parent_id'=>         array('User',              'one2one', 0, AF_OBLIGATORY|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'user'),
  ),
  
*/  

  "airport" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY, 2),
     'location_id'=>       array('Location',          'link', 0, 0,'location'),
     'code'=>              array('Code',              'str',   '', AF_OBLIGATORY|AF_UNIQUE, 3),
     'name'=>              array('Name',              'str',   '', 1, 100 ),
     'city'=>              array('City',              'str',   '', 1, 100 ),
     'country'=>           array('Country',           'many2one', 0, AF_HIDE_LIST, 'countries'),
     'location_accuracy'=>  array('Accuracy',          'map',    0, 0, 1),
     'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_bounds'      => array('Bounds'           , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
  ),
  

  "countries" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY, 2),
     'idd_prefix'=>        array('IDD Prefix',        'int',   0, AF_OBLIGATORY, 3),
     'name'=>              array('Name',              'str',   '', 1, 80 ),
  ),
  
  "currency" => 
  array(
     'code'=>              array('Code',              'str',   '', AF_PRIMARY, 3 ),
     'numeric_code'=>      array('Nunmeric Code',     'int',   '', 1, 3),
     'name'=>              array('Name',              'str',   '', 1, 50 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'accepted'=>          array('Accepted',          'bool',   0, 1),
     'minor_unit'=>        array('Minor Unit',        'int',   0, 0, 1),
  ),

  "user_level" => 
  array(
     'user_level'=>        array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'user_type'=>         array('Name',              'str',   '', 1, 12 ),
     'parent_object_type'=>array('Object type',       'str',   '', 0, 20 ),
  ),
  
  
  "user_role" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY, 2),
     'name'=>              array('Name',              'str',   '', 1, 20 ),
     'description'=>       array('Description',       'str',   '', 1, 255),
     'user_level'=>        array('ID',                'int',   0, 0, 2),
  ),
  

  "property_type" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'name'=>              array('Name',              'str',   '', 1, 20),
     'description'=>       array('Description',       'str',   '', 0, 80),
     'active'=>            array('Active?',           'bool',   1, 0),
     'hide'=>              array('Show?',             'bool',   0, 0),
     'bookable'=>          array('Bookable?',         'bool',   0, 0),
     'calendar'=>          array('Calendar?',         'bool',   0, 0),
     'hourly'=>            array('Hourly?',           'bool',   0, 0),
  ),
  
  "hosting_property_type" => 
  array(
     'id'=>             array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>           array('Name',              'str',   '', 1, 128 ),
     'description'=>   array('Description',        'str',   '', 1, 200 ),
     'active'=>            array('Active?',        'bool',   1, 0),
  ),
  
  "hosting_room_type" => 
  array(
     'id'=>             array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>           array('Name',              'str',   '', 1, 128 ),
     'description'=>   array('Description',        'str',   '', 1, 200 ),
     'active'=>            array('Active?',        'bool',   1, 0),
  ),
  
  "inv_type" => 
  array(
     'id'=>             array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>           array('Name',              'str',   '', 1, 20 ),
     'description'=>   array('Description',       'str',   '', 1, 200 ),
  ),
  
  
  "event_type" => 
  array(
     'id'=>             array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>           array('Name',              'str',   '', 1, 20 ),
     'description'=>    array('Description',       'str',   '', 1, 200 ),
     'property_types'=> array('Property types',    'msel',  '', AF_HIDE_LIST, 'property_type', array('active' => 1)),
  ),
  
  
  "lineitem_type" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>              array('Name',              'str',   '', 1, 20 ),
     'can_add'=>           array('User can add?',     'bool', 0, 0),
     'tax_category'=>      array('Tax Category',      'many2one',  0, AF_OBLIGATORY, 'tax_category', array('active' => 1)),
  ),
  
  
  "cc_type" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>              array('Name',              'str',   '', 1, 50 ),
  ),
  
  
  "tx_status" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>              array('Name',              'str',   '', 1, 50 ),
  ),
  
  
  "room_type" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>              array('Name',              'str',   '', 1, 20 ),
  ),
  
  
  "boat_type" =>                
  
  array(
     'id'               => array('ID'             ,'id',   0, AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE),
     'name'             => array('Name'           ,'str', '', AF_SEARCHABLE|AF_OBLIGATORY, 30),
     'description'      => array('Description'    ,'str', '', AF_SEARCHABLE|AF_OBLIGATORY, 255),
     'active'           => array('Active?'        ,'bool', 1, AF_SEARCHABLE),
     'searchable'       => array('Searchable?'    ,'bool', 1, AF_SEARCHABLE),
  ),
  
  
  "db_sequence" => 
  array(
     'seq_name'     => array('Table',              'str', '', AF_PRIMARY|AF_AUTOINCREMENT, 100),
     'nextid'       => array('Last ID',            'int', 11, AF_OBLIGATORY),
  ),

  "res_type" => 
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
     'description'=>   array('Description',       'str',   '', 1, 200 ),
  ),
  
  "rate_class" => 
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
     'description'=>   array('Description',       'str',   '', 1, 200 ),
  ),
  
  "address_type" => 
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
  ),
  
  "phone_type" => 
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
  ),
  
  "res_status" =>       
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
     'description'=>   array('Description',       'str',   '', 1, 200 ),
     'label'=>         array('Label class',       'str',   '', 0, 32 ),
     'color'=>         array('Color',             'color',   '000000', 0, 6),
  ),
          
  "site_role" =>       
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
     'description'=>   array('Description',       'str',   '', 1, 255 ),
  ),
            
  "event_status" => 
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
     'description'=>   array('Description',       'str',   '', 1, 200 ),
     'color'=>         array('Color',             'color',   '000000', 1, 6),
  ),
  
  
  "enq_status" => 
  array(
     'id'=>              array('ID',                  'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>            array('Name',                'str',   '', 1, 20 ),
     'description' =>    array('Description',         'str',   '', 1, 200 ),
     'color'=>           array('Color',               'color',   '000000', 1, 6),
  ),
  
  
  "inv_status" => 
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
     'description'=>   array('Description',       'str',   '', 1, 200 ),
     'color'=>         array('Color',             'color',   '000000', 1, 6),
  ),
  
  "pet_type" => 
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
     'description'=>   array('Description',       'str',   '', 1, 200 ),
  ),

  "pet_subtype" => 
  array(
     'id'=>            array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'type'=>          array('Type',              'many2one', 0, AF_OBLIGATORY, 'pet_type'),
     'name'=>          array('Name',              'str',   '', 1, 20 ),
     'description'=>   array('Description',       'str',   '', 1, 200 ),
  ),
  
  
  "country" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'grandparent_id'=>         array('Continent',         'many2one', 1, 0,'continent'),
     'location_id'=>       array('Location',          'link', 0, 0,'location'),
     'parent_id'=>         array('Region',            'many2one', 0, 0,'region'),
     'active'=>            array('Active',            'bool', 1, 0),
     'name'=>              array('Name',              'str',   '', AF_SEARCHABLE|AF_OBLIGATORY, 50 ),
     'alt_names'=>         array('Alt Names',         'text',   '', AF_SEARCHABLE),
     'priority'=>          array('Priority',          'float',  1, 0, '3.2'),
     'code'=>              array('Code',              'str',   '', 0, 3 ),
     'code2'=>             array('Code2',             'str',   '', 1, 2 ),                  
     'idd_code'=>          array('IDD Code (Regex)',  'str',   '', 0, 20),
     'mobile_regex'=>      array('Mobile Regex',      'str',   '', 0, 200),
     'tld'=>               array('TLD',               'str',   '', 0, 2),
     'location_id'      => array('Location'         , 'link', 0, AF_READONLY_EDIT, 'landmark'),
     'location_accuracy'=>  array('Accuracy',          'map',    0, 0, 1),
     'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_bounds'      => array('Bounds'           , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
     'tax_description'=>    array('Tax Description',   'str', '', AF_HIDE_LIST, 50),
  
     'tax_rate_li_types'=>  array('Taxed @ Rate (Hi)',     'msel','', 0, 'lineitem_type'),
     'tax_rate2_li_types'=> array('Taxed @ Rate 2 (Lo)',   'msel','', 0, 'lineitem_type'),
     'tax_rate3_li_types'=> array('Taxed @ Rate 3 (None)', 'msel','', 0, 'lineitem_type'),
     'tax_rate_category' => array('Tax Rate Category (Hi)', 'str', 'H', 0, 10),
     'tax_rate2_category' => array('Tax Rate Category (Lo)', 'str', 'H', 0, 10),
     'tax_rate3_category' => array('Tax Rate Category (None)', 'str', 'H', 0, 10),
  ),
  

/**
  "neighborhood" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'grandparent_id'=>    array('City',              'many2one', 0, AF_OBLIGATORY, 'city'),
     'parent_id'=>         array('Borough',           'many2one', 0, AF_OBLIGATORY, 'borough'),
     'active'=>            array('Active',            'bool',   0, 0),
     'name'=>              array('Name',              'str',   '', AF_SEARCHABLE|AF_OBLIGATORY, 50 ),
     'shortstay'=>         array('Shortstay',         'bool',   0, 0),
     'longstay'=>          array('Longstay',          'bool',   0, 0),
     'realestate'=>        array('Realestate',        'bool',   0, 0),
     'postcode_list'=>     array('Postcode list',     'str',   '', 0, 255 ),
     'description'=>       array('Description',       'text',  '', AF_HIDE_LIST),
     'location_id'      => array('Location'         , 'link', 0, AF_READONLY_EDIT, 'landmark'),
     'location_accuracy'=>  array('Accuracy',          'map',    0, 0, 1),
     'location_lat'=>       array('Latitude',          'float',  0, 0, '3.12'),
     'location_long'=>      array('Longitude',         'float',  0, 0, '3.12'),
     'location_bounds'      => array('Bounds'           , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
  ),
  
  
  "borough" => 
  array(
     'id'=>                 array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'grandparent_id'=>     array('District',          'many2one', 0, AF_OBLIGATORY, 'district'),
     'parent_id'=>          array('City',              'many2one', 0, AF_OBLIGATORY, 'city'),
     'active'=>             array('Active',            'bool',   0, 0),
     'name'=>              array('Name',              'str',   '', AF_SEARCHABLE|AF_OBLIGATORY, 50 ),
     'shortstay'=>          array('Shortstay',         'bool',   0, 0),
     'longstay'=>           array('Longstay',          'bool',   0, 0),
     'realestate'=>         array('Realestate',        'bool',   0, 0),
     'postcode_list'=>      array('Postcode list',     'str',   '', 0, 255 ),
     'description'=>        array('Description',       'text',  '', AF_HIDE_LIST),
     'location_id'      => array('Location'         , 'link', 0, AF_READONLY_EDIT, 'landmark'),
     'location_accuracy'=>  array('Accuracy',          'map',    0, 0, 1),
     'location_lat'=>       array('Latitude',          'float',  0, 0, '3.12'),
     'location_long'=>      array('Longitude',         'float',  0, 0, '3.12'),
     'location_bounds'      => array('Bounds'           , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
  ),
  
  
  "city" => 
  array(
    'id'=>                 array('ID',                    'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
    'grandparent_id'=>     array('Country',               'many2one', 0, 0,'country'),
    'parent_id'=>          array('District',              'many2one', 0, 0,'district'),
    'countrycode2'      => array('Country Code',          'str', '', 0, 2),
    'active'=>             array('Active',                'bool',   0, 0),
    'major'=>              array('Major',                 'bool',   0, 0),
     'name'=>              array('Name',              'str',   '', AF_SEARCHABLE|AF_OBLIGATORY, 50 ),
    'directory'=>          array('Directory',             'str',   '', 0, 50 ),
    'sale_min_price'=>     array('Realestate Min. Price', 'int',   0, AF_HIDE_LIST, 8 ),
    'rent_min_price'=>     array('Rental Min. Price',     'int',   0, AF_HIDE_LIST, 8 ),
    'MAS_city_id'=>        array('MAS id',                'int',   0, 0, 8 ),
    'MAS_apt_count'=>      array('MAS #apts',             'int',   0, 0, 8 ),
    'booking_city_id'=>    array('Booking id',            'int',   0, 0, 8 ),
    'booking_nrhotels'=>   array('Booking #hotels',       'int',   0, 0, 8 ),
    'description_en'=>     array('Description (English)', 'text', '', AF_HIDE_LIST),
    'description_nl'=>     array('Description (Dutch)',   'text', '', AF_HIDE_LIST),
    'description_fr'=>     array('Description (French)',  'text', '', AF_HIDE_LIST),
    'description_es'=>     array('Description (Spanish)', 'text', '', AF_HIDE_LIST),
    'description_ru'=>     array('Description (Russian)', 'text', '', AF_HIDE_LIST),
    'landmarks'=>          array('Landmarks',             'text', '', AF_HIDE_LIST),
     'location_id'      => array('Location'         , 'link', 0, AF_READONLY_EDIT, 'landmark'),
    'location_accuracy'=>  array('Accuracy',              'map',    0, 0, 1),
    'location_lat'=>       array('Latitude',              'float',  0, 0, '3.12'),
    'location_long'=>      array('Longitude',             'float',  0, 0, '3.12'),
    'location_bounds'      => array('Bounds'           , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
    'city_tax'=>           array('City Tax',           'surcharge', ATT_DEFAULT_NULL, 0),         
    'city_tax_description'=>   array('City Tax Description', 'str', '', AF_HIDE_LIST, 50),
    'city_boat_tax'=>           array('City Boat Tax',           'surcharge', ATT_DEFAULT_NULL, 0),         
    'city_boat_tax_description'=>   array('City Boat Tax Description', 'str', '', AF_HIDE_LIST, 50),
    'address_formatted'=> array('Adddress',          'text', '', AF_HIDE_LIST),
    
//    'count_shortstay'=>    array('Shortstay count',       'int',   0, 0, 8 ),
//    'count_boat'=>         array('Boat count',            'int',   0, 0, 8 ),
//    'count_realestate'=>   array('Realestate count',      'int',   0, 0, 8 ),
//    'count_longstay'=>     array('Longstay count',        'int',   0, 0, 8 ),
//    'count_office'=>       array('Office count',          'int',   0, 0, 8 ),
//    'count_hotel'=>        array('Hotel count',           'int',   0, 0, 8 ),
//    'count_property'=>     array('Property count',        'int',   0, 0, 8 ),
    
  ),
  
  
  "district" => 
  array(
     'id'=>                 array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'active'=>             array('Active',            'bool',   0, 0),
     'name'=>              array('Name',              'str',   '', AF_SEARCHABLE|AF_OBLIGATORY, 50 ),
     'parent_id'=>          array('Country',           'many2one', 1, 0,'country'),
     'grandparent_id'=>     array('Region',            'many2one', 1, 0,'region'),
     'location_accuracy'=>  array('Accuracy',          'map',    0, 0, 1),
     'location_id'      => array('Location'         , 'link', 0, AF_READONLY_EDIT, 'landmark'),
     'location_lat'=>       array('Latitude',          'float',  0, 0, '3.12'),
     'location_long'=>      array('Longitude',         'float',  0, 0, '3.12'),
     'location_bounds'      => array('Bounds'           , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
     'state_tax_rate'=>           array('Tax Rate',   'float',  0, AF_HIDE_LIST, '2.2'),
     'state_tax_description'=>    array('Tax Description',   'str', '', AF_HIDE_LIST, 50),
     'state_tax_rate_li_types'=>  array('Taxed @ High Rate', 'msel','', 0, 'lineitem_type'),
  ),
  
                                                                            
  
  "region" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'parent_id'=>         array('Country',           'many2one', 0, 0,'continent'),
     'active'=>            array('Active',            'bool',   0, 0),
     'name'=>              array('Name',              'str',   '', AF_SEARCHABLE|AF_OBLIGATORY, 50 ),
     'parent_id'=>         array('Continent',         'many2one', 1, 0,'continent'),
     'location_id'      => array('Location'         , 'link', 0, AF_READONLY_EDIT, 'landmark'),
    'location_accuracy'=>  array('Accuracy',          'map',    0, 0, 1),
     'location_lat'=>      array('Latitude',          'float',  0, 0, '3.12'),
     'location_long'=>     array('Longitude',         'float',  0, 0, '3.12'),
     'location_bounds'      => array('Bounds'           , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
  ),
  
  
  "continent" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'parent_id'=>         array('Parent (World)',    'int', 0, AF_HIDE), // dummy, used for consitency, always zero
     'active'=>            array('Active',            'bool',   0, 0),
     'name'=>              array('Name',              'str',   '', 1, 50 ),
     'location_id'      => array('Location'         , 'link', 0, AF_READONLY_EDIT, 'landmark'),
     'location_accuracy'=>  array('Accuracy',          'map',    0, 0, 1),
     'location_lat'=>      array('Latitude',          'float',  0, 0, '3.12'),
     'location_long'=>     array('Longitude',         'float',  0, 0, '3.12'),
     'location_bounds'      => array('Bounds'         , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
  ),
*/

  "location" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'site_id'=>           array('Site',              'link',  0, AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD, 'site'),
     'city_id'=>           array('City',              'link',   ATT_DEFAUL_NULL, AF_SEARCHABLE, 'geo_city'),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE),
     'active'=>            array('Active',            'bool', 1, 0),
     'priority'=>           array('Priority'          ,'int', 0, AF_HIDE, 8),

     'parent_type' =>      array('Parent Type',       'str', ATT_DEFAULT_NULL, 0, 50),
     'parent_id' =>        array('Parent ID',         'int', ATT_DEFAULT_NULL, 0),
     
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 50 ),
     'alt_names'=>         array('Alt Names',         'text',   '', AF_SEARCHABLE),
     'description'=>       array('Description',       'html',  '', AF_HIDE_LIST),                                 
     'slug'=>              array('Slug',              'slug',   '', AF_SEARCHABLE, 128 ),

     'address_street'=>    array('Street',            'str',  '', AF_HIDE_LIST, 50 ),
     'address_number'=>    array('Number',            'str',  '', AF_HIDE_LIST, 12 ),
     'address_city'=>      array('City',              'str',  '', AF_HIDE_LIST, 50 ),
     'address_postcode'=>  array('Postcode',          'str',  '', AF_HIDE_LIST, 50 ),
     'address_state'=>     array('State',             'str',  '', AF_HIDE_LIST, 50 ),
     'address_country'=>   array('Country',           'link', '', AF_HIDE_LIST, 'countries'),
     'address_formatted'=> array('Adddress',          'text', '', AF_HIDE_LIST),

     'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_accuracy'=> array('Accuracy',          'int',  0, 0),
     'location_zoom'=>     array('Zoom',              'int',  0, 0),
     'location_bounds' =>  array('Bounds',            'json', '', AF_HIDE_ADD|AF_HIDE_LIST),
     'location_radius' =>  array('Radius',            'int', DEFAULT_RADIUS, AF_HIDE_ADD|AF_HIDE_LIST),
     
     'media'                => array('Media',             'media',     '', 0, $property_media_options),
     'media_json'           => array('Media (json)',      'json',     ''),
   
  ),

  /** new geo system from: http://www.geonames.org/export/*/
  "geo_city" => 
  array(
    'id'=>                 array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
    'fid' =>               array('Foreign ID',        'int',  0, AF_HIDE_LIST),
    'active'=>             array('Active',             'bool',   1, AF_HIDE_LIST),
    'created'=>            array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY),
    'modified'=>           array('Modified',          'date',  ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),

    'name'=>               array('Name',              'str',   '', AF_SEARCHABLE|AF_OBLIGATORY, 50 ),
    'asciiname'=>          array('Name (ASCII)',      'slug',   '', AF_SEARCHABLE|AF_OBLIGATORY|AF_HIDE_LIST, 200 ),
    'alt_names'=>          array('Alt Names',         'text',   '', AF_SEARCHABLE|AF_HIDE_LIST),
    
     'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
    'location_bounds'   => array('Bounds',            'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
    'location_zoom'=>     array('Zoom',              'int',  0, 0),
                                                       
    'country_code' =>      array('Country Code',      'str', '', 0, 2),
    'cc2' =>               array('Alt.Country Codes', 'str', '', AF_HIDE_LIST, 200),

    'feature_class' =>     array('Feature Class',     'str', '', 0, 1),
    'feature_code' =>      array('Feature code',      'str', '', 0, 10),
                                                      
    'admin1_code' =>       array('Admin1 code',       'str', '', AF_HIDE_LIST, 20),
    'admin2_code' =>       array('Admin2 code',       'str', '', AF_HIDE_LIST, 80),
    'admin3_code' =>       array('Admin3 code',       'str', '', AF_HIDE_LIST, 20),
    'admin4_code' =>       array('Admin4 code',       'str', '', AF_HIDE_LIST, 20),


    'population'=>         array('Population',        'int',  0, 0, 8),
    'elevation'=>          array('Elevation',         'int',  0, AF_HIDE_LIST, 8),
    'dem'=>                array('Dem',               'int',  0, AF_HIDE_LIST, 8),

    'timezone' =>          array('Timezone',          'str', '', 0, 40),

    'city_tax'=>           array('City Tax',           'surcharge', ATT_DEFAULT_NULL, AF_HIDE_LIST),         
    'city_tax_description'=>   array('City Tax Description', 'str', '', AF_HIDE_LIST, 50),
    'city_boat_tax'=>           array('City Boat Tax',           'surcharge', ATT_DEFAULT_NULL, AF_HIDE_LIST),         
    'city_boat_tax_description'=>   array('City Boat Tax Description', 'str', '', AF_HIDE_LIST, 50),
    
  ),
  
  
  "landmark_type" => 
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 20),
     'description'=>        array('Description',       'str',   '', 1, 200 ),
  ),
  
  
  "landmark" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'active'=>            array('Active',            'bool',   1, 0),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE),
     'type'=>              array('Type',              'many2one',  0, AF_SEARCHABLE, 'landmark_type'),
//     'dummy'=>              array('Search',           'location_picker',  0, AF_DUMMY),
  
     'city_id'=>           array('City',              'many2one',   1000, AF_SEARCHABLE, 'geo_city', array('active' => 1)),
     'site_id'=>           array('Site',              'many2one',  0, AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD, 'site'),

     'parent_type' =>      array('Parent Type',       'str', ATT_DEFAULT_NULL, 0, 50),
     'parent_id' =>        array('Parent ID',         'int', ATT_DEFAULT_NULL, 0),
     
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 50 ),
  
     'address_street'=>    array('Street',            'str',   '', AF_HIDE_LIST, 50 ),
     'address_number'=>    array('Number',            'str',   '', AF_HIDE_LIST, 12 ),
     'address_state'=>     array('State',             'str',   '', AF_HIDE_LIST, 50 ),
     'address_postcode'=>  array('Postcode',          'str',   '', AF_HIDE_LIST, 50 ),
     'address_city'=>      array('City',              'str',   '', AF_HIDE_LIST, 50 ),
     'address_country'=>   array('Country',           'many2one', 0, AF_HIDE_LIST, 'countries'),
  
     'location_accuracy'    => array('Accuracy'    			, 'map',  0, 0),
     'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_bounds'      => array('Bounds'           , 'json', '', AF_HIDE_ADD|AF_HIDE_LIST, 200),
  
     'descriptions'=>       array('Descriptions',       'one2many', 0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_READONLY, 'object_description', 'parent_id', array('parent_type' => 'landmark')), // last is filter
  ),
  
  "golf_region" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'golf_country_id'=>   array('Golf Country',      'many2one', 0, 0, 'golf_country'),
     'level'=>             array('Level',             'int',   '', AF_SEARCHABLE, 1),
     'active'=>            array('Active',            'bool',   1, 0),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE),
     'source_id'=>         array('Source',            'link',   ATT_DEFAULT_NULL, 0, 'source'),
     'parent_id'=>         array('Parent',            'link',   0, 0, 'golf_region'),
     'location_id'=>       array('Location',          'link',   0, 0, 'location'),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 50 ),
     'code'=>              array('Code',              'str',   '', AF_SEARCHABLE, 10 ),
     'fid'=>               array('Foreign ID',        'str',   '', AF_SEARCHABLE, 10 ),
     'address'=>           array('Address',           'str',  '', AF_HIDE_LIST, 100),                                 
     'description'=>       array('Description',       'html',  '', AF_HIDE_LIST),                                 
     'country'    =>       array('Country',           'str',  '', 0, 2),
     'nr_clubs'=>          array('# Clubs',           'int',   '', AF_SEARCHABLE, 4 ),
  ),
/**
  "golf_country" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'active'=>            array('Active',            'bool',   1, 0),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY),
     'timestamp'=>         array('Timestamp',         'datetime',   ATT_DEFAULT_NOW, AF_HIDE),
     'location_id'=>       array('Location',          'link',   0, 0, 'location'),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 50 ),
     'code'=>              array('Code',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 10 ),
     'description'=>       array('Description',       'html',  '', AF_HIDE_LIST),                                 
  ),
  
  "golf_district" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'golf_country_id'=>   array('Golf Country',      'link', 0, AF_OBLIGATORY, 'golf_country'),
     'golf_region_id'=>    array('Golf Region',       'many2one', 0, AF_OBLIGATORY, 'golf_region'),
     'active'=>            array('Active',            'bool',   1, 0),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY),
     'timestamp'=>         array('Timestamp',         'datetime',   ATT_DEFAULT_NOW, AF_HIDE),
     'location_id'=>       array('Location',          'link',   0, 0, 'location'),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 50),
     'code'=>              array('Code',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 50),
     'address'=>           array('Address',           'str',  '', AF_HIDE_LIST, 100),                                 
     'description'=>       array('Description',       'html',  '', AF_HIDE_LIST),                                 
     'country'    =>       array('Country',           'many2one', 0, AF_OBLIGATORY, 'countries'),
  ),
*/

  "golf_club" => 
  array(
     'id'=>                 array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'active'=>             array('Active',            'bool',   1, 0),
     'priority'=>           array('Priority'          ,'int', 0, AF_HIDE, 8),

     'created'=>            array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY),
     'timestamp'=>          array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE),
     'site_id'=>            array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE_ADD, 'site'),
     'client_id'=>          array('Client',    		  	 'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),

     'source_id'=>          array('Source',            'link',   ATT_DEFAULT_NULL, 0, 'source'),
     'source_updated'=>     array('Source Updated',    'datetime',  ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),
     'source_url'=>         array('Source URL',        'url',   0, 0, 255),
     'fid'=>                array('Foreign ID',        'str', 0, 0, 10),
     'golf_region_id'=>     array('Golf Region',       'link',   ATT_DEFAULT_NULL, 0, 'golf_region'),
     'location_id'=>        array('Location',          'link',   0, 0, 'location'),
                            
     'name'=>               array('Name',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 255),
     'slug'=>               array('Slug',              'slug',   '', AF_OBLIGATORY|AF_SEARCHABLE, 128),
     'description'=>        array('Description',       'html',  '', AF_HIDE_LIST),                                 
                            
     // Leading Courses     
     'currency'=>           array('Currency',          'valSelect', 'EUR', AF_HIDE_LIST, $currencyArray),
     'currency_utf'=>       array('Currency UTF',      'str', '', AF_HIDE_LIST, 20),
     'currency_html'=>      array('Currency HTML',     'str', '', AF_HIDE_LIST, 20),
     'fee_weekend'=>        array('Fee weekend',       'money', 0, 0),
     'fee_weekday'=>        array('Fee weekday',       'money', 0, 0),

     'season_start'=>       array('Sesason Start',     'datetime',  ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),
     'season_end'=>         array('Season End',        'datetime',  ATT_DEFAULT_NULL, AF_HIDE_LIST|AF_READONLY),

     'nr_courses'=>         array('# courses',         'int',   0, 0, 3),
     'handicap_men'=>       array('Handicap men',      'float',   0, 0, '3.2'),
     'handicap_women'=>     array('Handicap women',    'float',   0, 0, '3.2'),

     'founded'=>            array('Founded',           'str',  '', AF_HIDE_LIST, 10 ),
     'formerly_known_as'=>  array('Formerly known as', 'str',  '', AF_HIDE_LIST, 128 ),
     'payment_options'=>    array('Payment Options',   'str',  '', AF_HIDE_LIST, 128 ),
     'allowed_cc'=>         array('Allowed CCs',       'str',  '', AF_HIDE_LIST, 128 ),

     'address_street'=>     array('Street',            'str',  '', AF_HIDE_LIST, 50 ),
     'address_number'=>     array('Number',            'str',  '', AF_HIDE_LIST, 12 ),
     'address_city'=>       array('City',              'str',  '', AF_HIDE_LIST, 50 ),
     'address_postcode'=>   array('Postcode',          'str',  '', AF_HIDE_LIST, 50 ),
     'address_state'=>      array('State',             'str',  '', AF_HIDE_LIST, 50 ),
     'address_country'=>    array('Country',           'link', '', AF_HIDE_LIST, 'countries'),
     'address_formatted'=>  array('Full address',      'str', '', AF_HIDE_LIST, 255),

     'source_url'=>         array('Source URL',        'url',   0, 0, 255),
     'booking_url'=>        array('Booking URL',       'url',   0, 0, 255),
     'address_web' =>       array('Web'                ,'str', '', 0, 255),

     'phone'  =>            array('Phone'              ,'str', '', 0, 20),
     'fax'  =>              array('Fax'                ,'str', '', 0, 20),
     'email_address' =>     array('Email'              ,'str', '', 0, 255),
     'facebook' =>          array('Facebook'           ,'str', '', 0, 255),
     'twitter' =>           array('Twitter'            ,'str', '', 0, 255),

     'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_radius'=>    array('Radius',            'int',  0, 0, 5),
                            
     'review_count'=>       array('Review Count',      'int',  0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST, 4),
     'review_score'=>       array('Review Score',      'float',  0, 0, '2.2'),
     'review_recommend'=>   array('# Recommend',       'int',    0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST, 4),

     /** from source - leading courses */
     'feedback_count'=>       array('# LC Reviews',    'int',  0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST, 4),
     
     'media_json'           => array('Media (json)',      'json',     ''),

     'facilities' =>        array('Facilities',        'msel','', AF_HIDE_LIST, 'facility', array('golf' => 1)),
     
     /** old */
     'review_nr'=>          array('# Reviews',         'int',  0, 0, 5),

     'images'  =>           array('Images',            'json', '', 0),     
     'image_count'  =>      array('# Images',          'int', 0, 0, 2),     
     'media'  =>            array('Media',             'media', '', 0, $property_media_options),     
     'media_count'  =>      array('# Media',           'int', 0, 0, 2),     

     'golf_courses'  =>     array('Golf courses',      'text', '', 0),     
     
  ),

  "golf_course" => 
  array(
     'id'=>                array('ID',                'id',     0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE_ADD, 'site'),
     'active'=>            array('Active',            'bool',   1, 0),
     'source_id'=>         array('Source',            'link',   0, 0, 'source'),
     'fid'=>               array('Foreign ID',        'str',    0, 0, 10),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE),
     'source_updated'=>    array('Source Updated',    'datetime', ATT_DEFAULT_NULL, AF_HIDE),
     'details_updated'=>   array('Details Updated',   'datetime', ATT_DEFAULT_NULL, AF_HIDE),

     'live_booking'=>      array('Live Booking',      'bool',   0, 0),

     'golf_club_id'=>      array('Golf Club',         'link',   ATT_DEFAULT_NULL, AF_OBLIGATORY, 'golf_club'),
     'golf_country_id'=>   array('Golf Country ID',   'link',   ATT_DEFAULT_NULL, 0, 'golf_country'),
     'golf_region_id'=>    array('Golf Region ID',    'link',   ATT_DEFAULT_NULL, 0, 'golf_region'),
     'golf_district_id'=>  array('Golf District ID',  'many2one',   ATT_DEFAULT_NULL, 0, 'golf_district'),

     'golf_country_code'=>   array('Golf Country',    'str', '', 0, 10),
     'golf_region_code'=>    array('Golf Region',     'str', '', 0, 20),
     'golf_district_code'=>  array('Golf District',   'str', '', 0, 50),

     'location_id'=>       array('Location',          'link',   0, 0, 'location'),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 50),                                 
     'short_description'=> array('Short Description', 'html',  '', AF_HIDE_LIST),
     'description'=>       array('Description',       'html',  '', AF_HIDE_LIST),                                 
     'course_type'=>       array('Type',              'str',   '', 0, 50),                                 
     'currency'=>          array('Currency',          'valSelect', 'EUR', AF_HIDE_LIST, $currencyArray),
     'fee_weekend'=>       array('Fee weekend',       'money', 0, 0),
     'fee_weekday'=>       array('Fee weekday',       'money', 0, 0),
     'fee_weekday_low'=>   array('Fee weekday (Low Season)', 'money', 0, 0),
     'fee_weekend_low'=>   array('Fee weekend (Low Season)', 'money', 0, 0),
     'number_holes'=>      array('Number holes',      'int',   0, 0, 3),
     'signature_hole'=>    array('Signature hole',    'str',   '', 0, 64),
     'par_men'=>           array('Par men',           'float',   0, 0, "2.1"),
     'par_women'=>         array('Par women',         'float',   0, 0, "2.1"),
     'slope_men'=>         array('Slope men',         'float',   0, 0, "2.1"),
     'slope_women'=>       array('Slope women',       'float',   0, 0, "2.1"),
     'length_men'=>        array('Length men',        'float',   0, 0, "4.1"),
     'length_women'=>      array('Length women',      'float',   0, 0, "4.1"),
     'rating_men'=>        array('Rating men',        'float', 0, 0, '2.2'),
     'rating_women'=>      array('Rating women',      'float', 0, 0, '2.2'),
     'architect'=>         array('Architect',         'text',  '', AF_HIDE_LIST),
     'image_base'  =>      array('Image Base',        'str', '', 0, 255),
     'image'  =>           array('Image',             'str', '', 0, 255),
     'images'  =>          array('Images',            'text', '', 0),
     'media'  =>           array('Media',             'media', '', 0, $property_media_options),

     // Golf switch
     'advance_days'=>       array('Advance days',     'int',   0, 0, 3),
     'inside_days'=>        array('Inside days',      'int',   0, 0, 3),
     
     'address_street'=>     array('Street',            'str',  '', AF_HIDE_LIST, 50 ),
     'address_number'=>     array('Number',            'str',  '', AF_HIDE_LIST, 12 ),
     'address_city'=>       array('City',              'str',  '', AF_HIDE_LIST, 50 ),
     'address_postcode'=>   array('Postcode',          'str',  '', AF_HIDE_LIST, 50 ),
     'address_state'=>      array('State',             'str',  '', AF_HIDE_LIST, 50 ),
     'address_country'=>    array('Country',           'link', '', AF_HIDE_LIST, 'countries'),
     'greens' =>            array('Greens',            'str',  '', AF_HIDE_LIST, 50 ),
     'notes' =>             array('Notes',             'html', '', AF_HIDE_LIST),
     'rating_count' =>      array('Rating Count',      'int',  '', AF_HIDE_LIST, 4),
     'allowed_cc' =>        array('Allowed CC',        'str',  '', AF_HIDE_LIST, 50),
     'allowed_players' =>   array('Allowed Players',   'str',  '', AF_HIDE_LIST, 50),
     'year_built' =>        array('Year Built',        'str',  '', AF_HIDE_LIST, 4),
     'dress_code' =>        array('Dress Code',        'str',  '', AF_HIDE_LIST, 100),
     'services' =>          array('Services',          'text', '', AF_HIDE_LIST, 50),
     'payment_terms' =>     array('Payment Terms',     'str',  '', AF_HIDE_LIST, 50),
     'price_from' =>        array('Price From',        'money','', 0),
     'price_to' =>          array('Price To',          'money','', 0),

     'scorecard' =>         array('Scorecard',         'json', '', AF_HIDE_LIST), 
     'cancel_type' =>       array('Cancellation Unit', 'str',  '', AF_HIDE_LIST, 50), 
     'cancel_count' =>      array('Cancellation Count','int',  '', AF_HIDE_LIST, 4), 
     'cancel_desc' =>       array('Cancellation Desc.','text', '', AF_HIDE_LIST, 50), 
      
),    
  

  "language" => 
  array(
  //         'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'code'=>              array('Code',              'str',   '', AF_PRIMARY, 3 ),
     'name'=>              array('Name',              'str',   '', 1, 50 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'allow_input'=>       array('Allow input?',      'bool',   1, 1),
     'locale'=>            array('Locale',            'str',   '', 1, 10 ),
  ),
  
  "client" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY, 6 ),
     'modified'=>          array('Modified',          'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 50 ),
     'shortname'=>         array('Short Name',        'str',   '', AF_OBLIGATORY, 10 ),
  
     'address_id'=>        array('Address',              'one2one',    0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'address'), // |AF_ONE2ONE_INTEGRATE
     'cities'=>            array('Cities',            'msel',     '', AF_HIDE_LIST, 'geo_city', array('active' => 1), 'name'),
     'types'=>             array('Property Types',    'msel',     '', AF_HIDE_LIST, 'property_type'),
     'language'=>           array('Language',    			'many2one', 'en', AF_OBLIGATORY|AF_SEARCHABLE, 'language'),                               
     'languages'=>         array('Languages',         'json',     '', AF_HIDE_LIST, 'language'),
     'mollie_profile'=> array('Mollie Profile', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 8),
  ),
  
  
  "legal_entity" => 
  array(
     'id'=>                  array('ID',                 'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'name'=>                array('Name',               'str',   '', 1, 100 ),
                             
     'client_id'=>           array('Client',    			   'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),
  
     'bank_name'=>           array('Bank name',          'str',   '', AF_HIDE_LIST, 100),
     'account_name'=>        array('Account name',       'str',   '', AF_HIDE_LIST, 100),
     'account_number'=>      array('Account number',     'str',   '', AF_HIDE_LIST, 200),
     'tax_id'=>              array('Legal/tax id',       'str',   '', AF_HIDE_LIST, 100),
     'commerce_id'=>         array('Business association id',  'str',   '', AF_HIDE_LIST, 100 ),
     'paypal_id_business' => array('Paypal ID Business', 'str',  '', AF_HIDE_LIST, 80),
     'paypal_id_private'  => array('Paypal ID Private',  'str',  '', AF_HIDE_LIST, 80),
  
     'logo'   =>           array('Logo',                 'image',      '', AF_HIDE_LIST, 128),
     'logo_small' =>       array('Logo - Small',         'image',   '', AF_HIDE_LIST, 128),
     'logo_print' =>       array('Logo - Print',         'image',   '', AF_HIDE_LIST, 128),
     'address_id'=>        array('Address',              'one2one',    0, AF_HIDE_LIST|AF_CASCADE_DELETE|AF_ONE2ONE_INTEGRATE, 'address'), // |AF_ONE2ONE_INTEGRATE
  
     'invoice_prefix'=>    array('Invoice Prefix',        'str',   '', 0, 10),
     'invoice_nextid'=>    array('Invoice Next ID',       'int',   1000, 0, 6),
     'invoice_id_required'=>  array('Invoice ID Required?',    'bool',   0, 0, 1),
  
     'reeleezee_username'=>    array('Reeleezee Username',  'str',   '', 0, 50),
     'reeleezee_password'=>    array('Reeleezee Password',  'str',   '', 0, 50),
     
     'mollie_id'=>      array('Mollie ID', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 8),
     'mollie_profile'=> array('Mollie Profile', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 8),
  
     'charge_tax' =>               array('Charge V.A.T?'       ,'bool', 0, AF_LOG, 0),
     'tax_included' =>             array('Tax included?'       ,'bool', 0, AF_LOG, 0),
  
     ),
  
  
  
  "server" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'date',   ATT_DEFAULT_TODAY, AF_HIDE_LIST|AF_READONLY, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'production'=>        array('Production Server?', 'bool',   0, 1),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 100 ),
     'description'=>       array('Description',       'text',  '', AF_HIDE_LIST, 255),
  
     'hostname'=>          array('Hostname',          'str',  '', AF_OBLIGATORY|AF_READONLY_EDIT, 100 ),
     'ip'=>                array('IP',                'ip',   '', AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 10 ),
     'country'=>           array('Country',           'many2one', 0, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 'countries'),
  
     'webroot'=>           array('Web root',           'str',   '/web/sites/', AF_HIDE_LIST, 100),
     'imageroot'=>         array('Image root',         'str',   '/web/images/', AF_HIDE_LIST, 100),
     'dataroot'=>          array('Data root',         'str',   '/web/data/', AF_HIDE_LIST, 100),
     'logdir'=>            array('Log dir',           'str',   '/web/logs/', AF_HIDE_LIST, 100),
  
     'apachename'=>        array('Apache name',       'str',   'apache2', AF_HIDE_LIST, 20),
  
     'db_type'=>           array('DB name',           'valSelect',   'mysql', 0, $db_type_array),
     'db_db'=>             array('DB name',           'str',   '', 0, 50),
     'db_user'=>           array('DB user',           'str',   '', AF_HIDE_LIST, 20),
     'db_password'=>       array('DB password',       'password',   '', AF_HIDE_LIST, 50),
     
  ),
  
  
  "site_template" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'date',   ATT_DEFAULT_TODAY, AF_HIDE_LIST|AF_READONLY, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 50 ),
     'description'=>       array('Description',       'text',  '', AF_HIDE_LIST),
//     'css_id'=>            array('CSS',               'many2one', 1000, AF_HIDE_LIST, 'site_css'),
     'skel_directory'=>    array('Skel Directory',    'str', 'html5', 0, 255),
     'html'=>              array('HTML',              'text',  '', AF_HIDE_LIST),         
  ),
  
  
  "site_css" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'date',   ATT_DEFAULT_TODAY, AF_HIDE_LIST|AF_READONLY, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 50 ),
     'description'=>       array('Description',       'text',  '', AF_HIDE_LIST),
     'css'=>               array('CSS',               'text',  '', AF_HIDE_LIST),         
     'preview_html'=>      array('Preview file',      'file',   '', 0, 50 ),
     'preview_image'=>     array('Preview thumb',     'file',   '', 0, 50 ),
  ),
  
  
  "site_stylesheet" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'date',   ATT_DEFAULT_TODAY, AF_HIDE_LIST|AF_READONLY, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 50 ),
     'description'=>       array('Description',       'text',  '', AF_HIDE_LIST),
  //         'css'=>               array('CSS',               'text',  '', AF_HIDE_LIST),         
     'styles'=>            array('Styles',    			  'one2many', '', AF_CASCADE_DELETE, 'site_style', 'stylesheet_id'),                               
     'preview_html'=>      array('Preview file',      'file',   '', 0, 50 ),
     'preview_image'=>     array('Preview thumb',     'file',   '', 0, 50 ),
  ),
  
  
  "site_style" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'stylesheet_id'=>     array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'date',   ATT_DEFAULT_TODAY, AF_HIDE_LIST|AF_READONLY, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'selector'=>          array('Selector',          'str',   '', AF_OBLIGATORY, 255),
     'style'=>             array('Style',           'text',  '', AF_HIDE_LIST),         
  ),
  
  
  // per language defaults for site      
  "site_content" => 
  array(
     'id'=>                array('ID',                  'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'site_id'=>           array('Site',                'many2one',  0, AF_SEARCHABLE|AF_HIDE, 'site'),
  
     'created'=>           array('Created',             'datetime',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>         array('Timestamp',           'timestamp',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
  
     'active'=>            array('Active?',             'bool',     1, 0),
  
     'language'=>           array('Language',    			  'many2one', 'en', AF_OBLIGATORY|AF_SEARCHABLE, 'language'),                               
     'title'=>             array('Screen Title',        'str',  '', AF_OBLIGATORY, 255 ),
     'subtitle'=>          array('Screen Subtitle',     'str',  '', AF_HIDE_LIST, 255),
  
     'se_title'=>          array('Search Engine Title',       'str',  '__pagename __pathvar __sitename', AF_HIDE_LIST, 255),
     'se_description'=>    array('Search Engine Description', 'text', '__pagename __pathvar __sitename', AF_HIDE_LIST),
     'se_keywords'=>       array('Search Engine Keywords',    'text', '', AF_HIDE_LIST),
  
     'site_header'=>           array('Header (HTML)',            'html', '', AF_HIDE_LIST),
     'site_footer'=>           array('Footer (HTML)',            'html', '', AF_HIDE_LIST),
     'site_extra'=>            array('Extra  (HTML)',            'html', '', AF_HIDE_LIST),
                                                                                         
     'mail_header'=>           array('Header (HTML)',            'html', '', AF_HIDE_LIST),
     'mail_footer'=>           array('Footer (HTML)',            'html', '', AF_HIDE_LIST),
     
     'alt_site_id'=>     array('Alternate Site for this language', 'many2one', ATT_DEFAULT_NULL, 0, 'site'),
     'machine_translated'=>    array('Machine Translated on',    'str',  '', AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 20),
              
     
  ),
    
  "property_config" => 
  array(
     'id'=>                    array('ID',                   'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),                                  
     'default_city'=>          array('Default City',         'many2one',  0, AF_HIDE_LIST, 'geo_city'),
     'show_cities'=>           array('Show cities',          'msel', '', AF_HIDE_LIST, 'geo_city', array('active' => 1), 'name'),
     'show_types'=>            array('Show types',           'msel', 101, AF_HIDE_LIST, 'property_type', array('active' => 1)),
     'property_filters' =>     array('Property Filters',     'text', '', AF_HIDE_LIST|AF_HIDE_ADD),
     'partner_filters'=>       array('Partner Filters',      'text', '', AF_HIDE_LIST|AF_HIDE_ADD, 255),
     'charge_service_fee' =>   array('Charge Service Fee',   'bool', 0, 0),
     
     
     'items_per_page'=>        array('Properties per page',  'int',  5, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'hide_local'=>            array('Hide Locally',         'bool', 0, 0, ''),         
     // 'template' =>             array('Template',             'valSelect', 'air', 0, assoc_array(array('afr', 'baris'))),
     'default_view' =>         array('Default view',         'valSelect', 'gallery', 0, assoc_array(array('gallery', 'list'))),          
     'thumb_size' =>           array('Thumb size',           'valSelect', 'small', 0, assoc_array(array('thumb', 'small'))),
     'show_request_form' =>    array('Show request form',    'bool', 1, 0),
     'show_hits' =>            array('Show hits',            'bool', 1, 0),
     'show_search' =>          array('Show search',          'bool', 1, 0),
     'show_sort' =>            array('Show sort',            'bool', 0, 0),
     'show_nav' =>             array('Show nav',             'bool', 0, 0),
     'show_map' =>             array('Show map',             'bool', 1, 0),
     'show_popup_map' =>       array('Show popup map',       'bool', 1, 0),
     'show_city_chooser' =>    array('Show city chooser',    'bool', 1, 0),
     'show_links' =>           array('Show links',           'bool', 1, 0),
     'show_feedback_city' =>   array('Show feedback city',   'bool', 1, 0),
     'show_feedback_date' =>   array('Show feedback date',   'bool', 1, 0),
     'show_feedback_surname'=> array('Show feedback surname','bool', 1, 0),
     'ajax_scroll' =>          array('Ajax scroll',          'bool', 0, 0),
     'content_box' =>          array('Content box',          'bool', 0, 0),
     'box_list_item' =>        array('Box list item',        'bool', 1, 0),                                                                      
    ),

  "site_config" => 
  array(
     'id'=>                   array('ID',                  'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),                                  

     'allow_ads'=>            array('Allow Ads',           'bool',     0, AF_HIDE_LIST),
     'add_pages'=>            array('Pages to add',        'flags', 0, 0, $__CMS_ADD_FLAGS),
     'show_site_logo'=>       array('Show logo on site?', 'bool', 1, 0, ''),         
     'show_mail_logo'=>       array('Show logo in mails?', 'bool', 1, 0, ''),         
     'show_mail_contact'=>    array('Show name in mails?', 'bool', 1, 0, ''),         
     'allow_user_login'=>     array('Allow user login?',   'bool', 0, 0),         
     'allow_user_register'=>  array('Allow user register?',   'bool', 0, 0),         
     'no_index' =>            array('No index?',           'bool', 0, 0),
     'no_follow' =>           array('No follow?',          'bool', 0, 0),
     'payment_options'=>      array('Accepted payments ',  'msel', '10,60,80,160', 0, 'payment_type', array('user_select' => 1)),
     'show_cart'=>            array('Show shopping cart?', 'bool', 0, 0),
     'user_roles'=>           array('User Roles',          'flags', 114689, 0, $__USER_ROLES),
     'landing_page' =>        array('Landing Page',        'json', '', 0)
    ),
  
  
  // used by affiliates and sites to configure dimensions (width/height)      
  "site_dim" => 
  array(
     'screen_width'=>         array('Width',                'int',      1280, AF_OBLIGATORY|AF_HIDE_LIST, 4),
                                          
     'column_width'=>         array('Column Width',         'int',      200, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'column_width_wide'=>    array('Wide Column Width',    'int',      250, AF_OBLIGATORY|AF_HIDE_LIST, 4),

     'box_margin'=>           array('Box margin',           'str',      '8', AF_OBLIGATORY|AF_HIDE_LIST, 20),
     'box_padding'=>          array('Box padding',          'str',      '8', AF_OBLIGATORY|AF_HIDE_LIST, 20),
     'content_margin'=>       array('Content margin',       'str',      '15,31', AF_OBLIGATORY|AF_HIDE_LIST, 20),
     'font_size'=>            array('Font size',            'int',      12, AF_OBLIGATORY|AF_HIDE_LIST, 2),
     'column_spacing'=>       array('Column spacing',       'int',      10, AF_OBLIGATORY|AF_HIDE_LIST, 2),

     'thumb_pic_width'=>      array('Thumb Picture Width',      'int',      100, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'square_pic_width'=>     array('Square Picture Width',     'int',      200, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'small_pic_width'=>      array('Small Picture Width',      'int',      200, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'medium_pic_width'=>     array('Medium Picture Width',     'int',      640, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'big_pic_width'  =>      array('Big Picture Width',        'int',      1280, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'full_pic_width' =>      array('Full Picture Width',       'int',     1920, AF_OBLIGATORY|AF_HIDE_LIST, 4),     

/*     
     'content_width'=>        array('Content Width',        'int',      980, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'screen_height'=>        array('Height',               'int',      0, AF_HIDE_LIST, 4),
     'inner_width'=>          array('Inner Width',          'int',      720, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'wide_column_width'=>    array('Wide Column Width',    'int',      300, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'narrow_column_width'=>  array('Narrow Column Width',  'int',      200, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'center_column_width'=>  array('Center Column Width',  'int',      450, AF_OBLIGATORY|AF_HIDE_LIST, 4),
     'category_column_width'=>    array('Category Column Width',    'int',      300, AF_OBLIGATORY|AF_HIDE_LIST, 4),
*/

    ),
  
 
  "site" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'parent_site_id'=>    array('Parent site',       'many2one', 0, 0, 'site'),
     'source_site_id'=>    array('Source site',       'many2one', 0, 0, 'site'),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
     'active'  =>           array('Active?',          'bool',     1,  AF_HIDE_ADD, 0),
  
     'legal_entity_id'=>   array('Legal Entity',      'many2one', 0, AF_OBLIGATORY, 'legal_entity'),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),
     'address_id'=>        array('Address',           'one2one',    0, AF_HIDE_LIST|AF_ONE2ONE_INTEGRATE|AF_CASCADE_DELETE, 'address'), // |AF_ONE2ONE_INTEGRATE
  
     'languages'=>            array('Languages',    	'json', 'en', AF_OBLIGATORY, 'language', array('active' => 1)),
     'default_language'=>     array('Language',    		'valSelect', 'en', AF_OBLIGATORY|AF_SEARCHABLE, $langArray),
     
     'template' =>         array('Template',          'str', '', 0, 128),
     'template_id'=>       array('Template ID',       'many2one', 1014, AF_HIDE_LIST, 'site_template', array('skel_directory' => array('!=', ''))), // baris
     //'css_id'=>            array('CSS',               'many2one', 1167, AF_HIDE_LIST, 'site_css'),
  
     //'config_id'=>          array('Config',            'one2one', 0, AF_HIDE_LIST|AF_ONE2ONE_INTEGRATE, 'site_config'),
     //'scheme_id'=>          array('Scheme',            'one2one', 0, AF_HIDE_LIST|AF_ONE2ONE_INTEGRATE, 'site_scheme'),
     //'dim_id'=>             array('Dimensions',        'one2one', 0, AF_HIDE_LIST|AF_ONE2ONE_INTEGRATE, 'site_dim'),
     //'property_config_id'=> array('Property Config',   'one2one', 0, AF_HIDE_LIST|AF_ONE2ONE_INTEGRATE, 'property_config'),
  
     'theme_color'=>        array('Theme Color',        'color',    '474747', AF_HIDE_LIST, 6),
     
     'built'  =>            array('Built?',             'bool', 0, AF_HIDE_ADD, 0),
     'live'   =>            array('Live?',              'bool', 0,  AF_HIDE_ADD, 0),
     'secure'   =>          array('Secure?',            'bool', 0,  AF_HIDE_ADD, 0),
     'roles'=>              array('Roles',              'msel', '', 0, 'site_role'),
     
     'name'=>              array('Name / Title',      'str',   '', 1, 100 ),
     'shortname'=>         array('Shortname',         'str',   '', AF_OBLIGATORY|AF_UNIQUE, 50),
     'library_prefix'=>    array('Libarary Prefix',   'str',   '', AF_HIDE_ADD, 20),
     'domain'=>            array('Domain (w/o www.)', 'str',   '', 1, 100 ),
     'url'=>               array('URL',               'url',   '', AF_HIDE_LIST|AF_HIDE_ADD, 100 ),
     'test_url'=>          array('URL - test server', 'url',   '', AF_HIDE_LIST|AF_HIDE_ADD, 100 ),
  
     'app_server'=>        array('App. Server',       'many2one',   SYSTEM_SERVER_ID, AF_OBLIGATORY|AF_HIDE_ADD|AF_READONLY, 'server'),
     'dev_server'=>        array('Dev. Server',       'many2one',   DEV_SERVER_ID, AF_OBLIGATORY|AF_HIDE_ADD, 'server'),
     'live_server'=>       array('Live Server',       'many2one',   '', AF_OBLIGATORY, 'server', array('active' => 1, 'production' => 1)),
     // 'db_server'=>         array('DB Server',         'many2one',   SYSTEM_SERVER_ID, AF_READONLY, 'server'),
     // 'db_dev_server'=>     array('DB Dev Server',     'many2one',   SYSTEM_DEV_SERVER_ID, AF_READONLY, 'server'),
  
     'directory'=>         array('Directory',         'str',   '', AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 255),
     //'dev_directory'=>     array('Dev Directory',    'str',   '', AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 255),
     'test_directory'=>    array('Test Directory',    'str',   '', AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 255),
     //'image_directory'=>   array('Image dir',         'str',   '/i/', AF_HIDE_LIST|AF_HIDE_ADD, 20),
     //'auto_build'=>        array('Auto Build?',       'bool',   1, AF_HIDE_LIST),
  
     'email_forward'=>      array('Forward email to:', 'email',  '' , AF_OBLIGATORY|AF_HIDE_LIST, 100),
  
     //'google_translate'=>  array('Google Translate?', 'bool',   0, AF_HIDE_LIST),
     'googlemap_live_key'=> array('Google Map Key (Live)', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 100),
     'googlemap_test_key'=> array('Google Map Key (Test)', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 100),
     'googlemap_dev_key' => array('Google Map Key (Dev)',  'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 100),
     'google_analytics_id'=> array('Google Analytics ID', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 20),
     'google_username'=>     array('Google Username',  'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 100),
     'google_pass'=>         array('Google Password',  'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 100),
     'google_id'=>           array('Google ID',  'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 100),
     'google_tag_id'=>      array('Google Tag ID',  'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 32),
  
     'mollie_profile' => array('Mollie Profile', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 8),
     'mollie_live_key'=> array('Mollie Live Key', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 40),
     'mollie_test_key'=> array('Mollie Test Key', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 40),
     'bitpay_api_key'=> array('Bitpay API Key', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 40),
     'paypal_api_username' => array('PayPal API username', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 50),
     'paypal_api_password'=> array('PayPal API password', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 50),
     'paypal_api_signature'=> array('PayPal API signature', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 60),
  
     'facebook_id'    => array('Facebook ID', 'str',   '', AF_HIDE_LIST|AF_HIDE_ADD, 50),

     'social_facebook'  => array('Facebook Page', 'str',   '', AF_HIDE_LIST, 50),
     'social_twitter'   => array('Twitter Page',  'str',   '', AF_HIDE_LIST, 50),
     'social_linkedin'  => array('Linkedin Page', 'str',   '', AF_HIDE_LIST, 50),
     'social_hyves'     => array('Hyves Page',    'str',   '', AF_HIDE_LIST, 50),
     'social_youtube'   => array('Youtube Page',  'str',   '', AF_HIDE_LIST, 50),
     
     'sms_credits' =>                         array('sms_credits',                 'int', 0, AF_HIDE_LIST),
     'google_translate_characters' =>        array('google_translate_characters',  'int', 0, AF_HIDE_LIST),

     'rental_geodir'=>        array('Use city directory for rentals?',       'bool', 0, 0),
     'gallery_site'=>         array('Gallery site?',       'bool', 0, 0),
     'property_site'=>         array('Property site?',       'bool', 0, 0),
     'property_type'=>         array('Property type',       'str', '', 32),
     'property_sort'=>         array('Property sort',       'str', '', 64),
     'golf_site'=>             array('Golf site?',       'bool', 0, 0),
     'pet_site'=>             array('Pet site?',       'bool', 0, 0),

     'require_user_login'=>   array('Require user login?',   'bool', 0, 0),         
     'allow_user_login'=>     array('Allow user login?',    'bool', 0, 0),         
     'allow_user_register'=>  array('Allow user register?',   'bool', 0, 0),         
     'logo'   =>              array('Logo',                 'image',   '', AF_HIDE_LIST, 128),
     'logo_small' =>          array('Logo - Small',         'image',   '', AF_HIDE_LIST, 128),
     'logo_print' =>          array('Logo - Print',         'image',   '', AF_HIDE_LIST, 128),
     'default_city'=>         array('Default City',         'many2one',  0, AF_HIDE_LIST, 'geo_city'),
     'show_cities'=>          array('Show cities',          'msel', '', AF_HIDE_LIST, 'geo_city'),
     'show_types'=>           array('Show types',           'msel', '', AF_HIDE_LIST, 'property_type'),
     'default_bounds'=>       array('Default Bounds',       'json',  0, AF_HIDE_LIST),

     'property_filters' =>    array('Property Filters',     'json', '', AF_HIDE_LIST|AF_HIDE_ADD),
     'partner_filters'=>      array('Partner Filters',      'json', '', AF_HIDE_LIST|AF_HIDE_ADD),
     'cloudinary'=>      array('Cloudinary Config',      'json', '', AF_HIDE_LIST|AF_HIDE_ADD),
     'charge_service_fee' =>  array('Charge Service Fee',   'bool', 0, 0),
     
     'pages'  =>            array("Pages",    'one2many', 0, AF_HIDE_LIST|AF_READONLY|AF_CASCADE_DELETE|AF_HIDE_ADD, 'page_content', 'site_id'),
     'content'  =>          array("Content",  'one2many', 0, AF_HIDE_LIST|AF_READONLY|AF_CASCADE_DELETE|AF_HIDE_ADD, 'site_content', 'site_id'),
       
  ),
  
  
  "page_type" => 
  array(
     'id'=>                array('ID',                 'id',   0, AF_PRIMARY|AF_AUTOINCREMENT),
     'name'=>              array('Name',               'str',   '', 1, 20),
     'description'=>       array('Description',        'str',   '', 0, 80),

     'template'=>          array('Default template',   'str', '', 0, 128),
     'controller'=>        array('Default controller', 'str', '', 0, 128),
     'user_level' =>       array('User level',         'int',  0, 0),  
     'show_menu'=>         array('Show in menu?',      'bool', 0, 0),
     
     'path_var'  =>        array('Path var',           'str', '', 0, 40),
     'object_type' =>      array('Obj type',           'str', '', 0, 50),
     'cms_add'=>           array('CMS auto-add?',      'flags',   0, 0, $__CMS_ADD_FLAGS),

     /** below are old */
     /**     
     'object_subtype' =>   array('Obj subtype',         'int', 0, AF_HIDE),
     'object_id' =>        array('Obj id',              'int', 0, AF_HIDE),
     
     'cms_show'=>          array('CMS show?',         'bool',   1, 0),
     'property'=>          array('Property',          'bool',   0, 0),

     'localized'=>         array('Localized?',          'bool',  1, 0),
     'secure'=>            array('Secure?',             'bool',  0, 0),
     'static'=>            array('Static?',             'bool',  0, 0),
     'relative'=>          array('Relative to city',    'bool',  0, 0),
     'admin'=>             array('Admin page?',         'bool',  0, 0),
     'dynamic'=>           array('Dynamic (no spider)?','bool',  0, 0),
     'external'=>          array('External?',           'bool',  0, 0),

     'show_footer'=>       array('Show link in footer?', 'bool',   0, 0),
     'show_title'=>        array('Show page title?',     'bool',   1, 0),
     'template_id'=>       array('Default template?',    'many2one', 0, 0, 'site_template'),
     */
  ),
  
  
  "site_page" => 
  array(
     'id'=>                array('ID',                  'id',       0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'created'=>           array('Created',             'datetime',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>         array('Timestamp',           'timestamp',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
     'active'=>            array('Active?',             'bool',     1, 0),
     'site_id'=>           array('Site',                'many2one',  0, AF_OBLIGATORY|AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD, 'site'),
     'template_id'=>       array('Template',            'many2one', 0, AF_HIDE_LIST, 'site_template'),
     'parent_id' =>        array('Parent page',         'many2one', '', AF_SEARCHABLE|AF_READONLY_ADD, 'site_page'),
     'user_id' =>          array('Author',              'link', ATT_DEFAULT_USER_ID, 0, 'user'),

     
     'name'=>              array('Name',                'str',  '', AF_OBLIGATORY, 50 ),
     'template'=>          array('Template file',        'str',  '', 0, 128 ),
     'controller'=>        array('Controller',           'str',  '', 0, 128 ),

     'page_type' =>        array('Page type',           'many2one', '', AF_SEARCHABLE, 'page_type'),
     'object_type' =>      array('Obj type',            'str', '', AF_HIDE, 50),
     'object_subtype' =>   array('Obj subtype',         'int', 0, AF_HIDE),
     'object_id' =>        array('Obj id',              'int', 0, AF_HIDE),
     'path_var'  =>        array('Path var',            'str', '', AF_HIDE, 40),
  
     'show_menu'=>         array('Show in menu?',       'bool', 1, AF_HIDE_LIST, 0),
     'user_level'=>        array('User Level',          'many2one',  0, AF_SEARCHABLE, 'user_level'),
     'rank'=>              array('Rank',                'int',  0, 0, 3),

     'is_folder' =>        array('Is folder?',          'bool', 0, 0),
     'local'=>             array('Local template?',     'bool', 0, 0),
 
  ),
  
  "page_content" =>  
  array(
     'id'=>                array('ID',                  'id',       0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'site_id'=>           array('Site',                'many2one',  0, AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD, 'site'),
     'page_id'=>           array('Parent Page',         'many2one',  0, AF_OBLIGATORY|AF_HIDE_EDIT, 'site_page'),
     'created'=>           array('Created',             'datetime',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>         array('Timestamp',           'timestamp',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
     'published'=>         array('Published?',          'bool',     0, AF_READONLY),
     'language'=>          array('Language',    			  'many2one', 'en', AF_OBLIGATORY|AF_SEARCHABLE, 'language'),
     'path'=>              array('Path',                'str',  '', AF_SEARCHABLE, 200 ),
     'title'=>             array('Screen Title',        'str',  '', AF_SEARCHABLE, 100 ),
     'subtitle'=>          array('Screen Subtitle',     'str',  '', AF_HIDE_LIST, 100 ),
     'menu_title'=>        array('Menu title',          'str',  '', AF_HIDE_LIST, 100 ),
     //'content'=>           array('Content (HTML)',            'html', '', AF_HIDE_LIST, 30),

     'se_title'=>          array('Search Engine Title',       'str',  '', AF_HIDE_LIST, 100 ),
     'se_keywords'=>       array('Search Engine Keywords',    'text', '', AF_HIDE_LIST, 255 ),
     'se_description'=>    array('Search Engine Description', 'text', '', AF_HIDE_LIST),
     

   ),  
  // generic 
  
  
  // language specific
  "page_element" =>  
  array(
     'id'=>                array('ID',                  'id',       0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'site_id'=>           array('Site',                'many2one',  0, AF_SEARCHABLE|AF_HIDE_EDIT|AF_HIDE_ADD, 'site'),
     'page_id'=>           array('Parent Page',         'many2one',  0, AF_OBLIGATORY|AF_HIDE_EDIT, 'site_page'),
     'created'=>           array('Created',             'datetime',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'rank'=>              array('Rank',                'int', 1, AF_HIDE_ADD, 3),
     'timestamp'=>         array('Timestamp',           'timestamp',     ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
     'language'=>          array('Language',    			  'many2one', 'en', AF_OBLIGATORY|AF_SEARCHABLE, 'language'),                               
     'name'=>              array('Name',                'str',  '', AF_OBLIGATORY|AF_SEARCHABLE, 100 ),
     'type'=>              array('Type',                'str',  '', AF_OBLIGATORY|AF_SEARCHABLE, 50 ),
     'content'=>           array('Content',             'text',  '', 0),
     'media' =>            array('Media',               'media', '', 0, $single_media_options),
     'resize' =>           array('Resize Media?',       'bool',  0, 0),
     'options'=>           array('Options',             'text',  '', 0),
   ),


  "font" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'name'=>              array('Name',              'str',   '', 1, 20 ),
     'css'=>               array('CSS',               'str',   '', 1, 255 ),
  ),
  

  "message" => 
  array(
     'id'=>                array('ID',                'id',       0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST, 14 ),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST, 14 ),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY_EDIT, 'client'),
     'site_id'=>           array('Site',              'many2one', ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'parent_id'=>         array('Parent Id',         'parent_id',   0, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 11),
     'parent_type'=>       array('Parent Type',       'parent_type', '', AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD),
     'remote_ip'=>         array('IP',                'ip',      ATT_DEFAULT_CLIENT_IP, AF_HIDE_ADD|AF_READONLY, 20 ),
      //'city_id'=>           array('City',              'many2one', ATT_DEFAULT_CITY_ID, AF_SEARCHABLE, 'geo_city', array('active' => 1), 'name'),
     'read'=>              array('Read',              'bool',     0, AF_HIDE_LIST),
     'replied'=>           array('Replied',           'bool',     0, AF_HIDE_LIST),
     'name'=>              array('Name',              'str',      '', AF_SEARCHABLE, 60 ),
     'title'=>             array('Title',             'str',      '', 0, 50 ),
     'company'=>           array('Company',           'str',      '', AF_SEARCHABLE, 60 ),
     'country'=>           array('Country',           'many2one', ATT_DEFAULT_CLIENT_CC, AF_HIDE_LIST, 'countries'),
     'language'=>          array('Language',          'many2one', ATT_DEFAULT_LANGUAGE, 0, 'language'),
     'subject'=>           array('Subject',           'str',      '', AF_SEARCHABLE, 60 ),
     'phone'=>             array('Phone',             'str',    '', AF_HIDE_LIST, 20),

     /** old */
     'message'=>           array('Message',           'text',     '', 0, 0),     
     'email_address'=>     array('Email',             'email',    '', AF_HIDE_LIST, 60),
     
     /** old */
     'main_message'=>      array('Main Message',      'text',     '', 0, 0),     
     'personal_message'=>  array('Personal Message',  'text',     '', 0, 0),     
     'sender'=>            array('Sender',            'str',      '', AF_HIDE_LIST, 128),
     'recipient'=>         array('Recipient',         'str',      '', AF_HIDE_LIST, 128),
  ),                                                            
  
  
  "reslog" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE, 11),
     'timestamp'=>         array('Timestamp',         'timestamp',  ATT_DEFAULT_NOW, AF_SEARCHABLE, 14),
     'res_id'=>            array('ResId',             'link',  1, AF_SEARCHABLE|AF_HIDE, 'reservation'),
     'user_id'=>           array('User',              'link',  ATT_DEFAULT_USER_ID, AF_SEARCHABLE, 'user'),
  //         'weblog_id'=>         array('Web log',           'link',  0, 0, 'weblog'),
     'action'=>            array('Action',            'str',   '', AF_SEARCHABLE, 100 ),
  ),
  
  
  "changelog" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE, 11),
     'timestamp'=>         array('Timestamp',         'timestamp',  ATT_DEFAULT_NOW, AF_SEARCHABLE, 14),
     //'obj_type'=>          array('Obj Type',          'str',   '', AF_HIDE, 20),
     //'parent_id'=>         array('ObjId',             'parent_id',  1, AF_SEARCHABLE|AF_HIDE, 'baseclass'),
     'obj_type'=>          array('Obj Type',          'str',   '', 0, 20),
     'parent_id'=>         array('ObjId',             'parent_id',  1, 0, 'baseclass'),
     'user_level'=>        array('User Level',        'many2one',  ATT_DEFAULT_USER_LEVEL, AF_SEARCHABLE, 'user_level'),
     'user_id'=>           array('User',              'many2one',  ATT_DEFAULT_USER_ID, AF_SEARCHABLE, 'user'),
     'field'=>             array('Field',             'str',   '', AF_SEARCHABLE, 50 ),
     'from_value'=>        array('Old value',         'str',   '', AF_SEARCHABLE, 255 ),
     'to_value'=>          array('New value',         'str',   '', AF_SEARCHABLE, 255 ),
     'action'=>            array('Action',            'str',   '', AF_SEARCHABLE, 255 ),
  ),
  
  
  "news" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'created'=>           array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'site_id'=>           array('Site',              'many2one',   ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'user_level'=>        array('User Level',        'many2one',  0, AF_SEARCHABLE, 'user_level'),
     'title'=>             array('Title',             'str',   '', AF_OBLIGATORY, 255),
     'content'=>           array('Content',           'html',  '', AF_HIDE_LIST|AF_OBLIGATORY),
     'language'=>          array('Language',    			'many2one', ATT_DEFAULT_LANGUAGE, AF_OBLIGATORY|AF_SEARCHABLE, 'language'),
     'image'=>             array('Image',             'image',  '', AF_HIDE_LIST, 128),
  ),
  
  
  
  "article" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE|AF_READONLY, 14 ),
     'post_date'=>         array('Article Date',      'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST, 6 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'published'=>         array('Published',         'bool',   0, 0),
     'type' =>             array('Article.Type',      'many2one', 0, AF_SEARCHABLE, 'article_type'),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'user_id'=>           array('User',              'link',  ATT_DEFAULT_USER_ID, AF_SEARCHABLE, 'user'),
     'user_level'=>        array('User Level',        'many2one',  0, AF_SEARCHABLE, 'user_level'),
     'salutation'=>        array('Salutation',        'valSelect', '', 0, $salutationArray),
     'first_name'=>        array('First Name',        'str',    '', AF_SEARCHABLE, 50),
     'last_name'=>         array('Last Name',         'str',    '', AF_SEARCHABLE, 50),
     'email_address'=>     array('Email',             'email',  '', AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'title'=>             array('Title',             'text',   '', 0, 255),
     'subtitle'=>          array('Subtitle',          'str',   '', 0, 255),
     'content'=>           array('Content',           'html',  '', AF_HIDE_LIST|AF_OBLIGATORY),
     'language'=>          array('Language',    			'many2one', ATT_DEFAULT_LANGUAGE, AF_OBLIGATORY|AF_SEARCHABLE, 'language'),
     'link'=>              array('URL',               'str',    '', AF_HIDE_ADD|AF_HIDE_LIST, 100),
     'image'=>             array('Image',             'image',  '', AF_HIDE_LIST, 128),
     'media'            => array('Media',             'media',     '', 0, $gallery_media_options),
     'views'=>             array('Views',             'int',    0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST),
     
     //array('type' => IMAGE_TYPE_PROFILE, 'resize' => true, 'minimum' => 640)),
  
  ),

  "comment" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'created'=>           array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'article_id'=>        array('Article',           'link',   ATT_DEFAULT_ARTICLE_ID, AF_READONLY, 'article', $article_filters),
     'comment_id'=>        array('Comment',           'link',   ATT_DEFAULT_COMMENT_ID, AF_READONLY, 'comment', $comment_filters),
     'user_id'=>           array('User',              'link',  ATT_DEFAULT_USER_ID, AF_SEARCHABLE, 'user'),
     'language'=>          array('Language',    			'many2one', ATT_DEFAULT_LANGUAGE, AF_OBLIGATORY|AF_SEARCHABLE, 'language'),
//     'salutation'=>        array('Salutation',        'valSelect', '', 0, $salutationArray),
     'first_name'=>        array('Name',              'str',    '', AF_OBLIGATORY|AF_SEARCHABLE, 50),
     'last_name'=>         array('Last Name',         'str',    '', AF_SEARCHABLE, 50),
     'email_address'=>     array('Email',             'email',  '', AF_OBLIGATORY|AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'title'=>             array('Title',             'str',   '', 0, 255),
     'content'=>           array('Content',           'html',  '', AF_OBLIGATORY|AF_HIDE_LIST|AF_OBLIGATORY),
  ),                                                                  
  
  "newsletter" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'created'=>           array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST, 6 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'remote_ip'=>         array('IP',                'ip',       ATT_DEFAULT_CLIENT_IP, AF_HIDE_LIST|AF_SEARCHABLE|AF_READONLY, 20),
     'remote_cc'=>         array('CC',                'many2one', ATT_DEFAULT_CLIENT_CC, AF_HIDE_LIST, 'countries'),
     'user_id'=>           array('User',              'link',  ATT_DEFAULT_USER_ID, AF_SEARCHABLE, 'user'),
     'first_name'=>        array('First Name',        'str',    '', AF_SEARCHABLE, 50),
     'last_name'=>         array('Last Name',         'str',    '', AF_SEARCHABLE, 50),
     'email_address'=>     array('Email',             'email',  '', AF_SEARCHABLE|AF_HIDE_LIST, 50),
     'language'=>          array('Language',    			'many2one', ATT_DEFAULT_LANGUAGE, AF_OBLIGATORY|AF_SEARCHABLE, 'language'),
  ),

  "media_collection_type" => 
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',               'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
     'description'=>        array('Description',        'str',   '', 0, 100),
  ),

  "media_collection" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'created'=>           array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'rank'=>              array('Rank',              'int', 0, AF_HIDE_ADD, 3),
     'type' =>             array('Collection Type',   'many2one', MEDIA_COLLECTION_TYPE_EXHIBITION, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 'media_collection_type'), // collection, exhibition
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE_ADD, 'site'),
     'user_id'=>           array('User',              'link',  ATT_DEFAULT_USER_ID, AF_SEARCHABLE|AF_HIDE_ADD, 'user'),
     'title'=>             array('Title',             'str',   '', AF_OBLIGATORY, 255),
//     'title_image'=>       array('Title Image',       'media',  ATT_DEFAULT_NULL, 0, 'media'),
     'title_image'=>       array('Title image',       'media',   '', 0, $std_image_options),
     'language'=>          array('Language',    			'many2one', ATT_DEFAULT_LANGUAGE, AF_OBLIGATORY|AF_SEARCHABLE, 'language'),
     'description'=>       array('Description',       'html',  '', AF_HIDE_LIST),
//     'json' =>             array('Json',              'json',  '', AF_READONLY),
//     'images'=>            array('Images',            'many2many', '', AF_HIDE_LIST, 'media_collection_map'),
     'start_date'=>         array('From',              'date',   '', AF_LOG),
     'end_date'=>           array('To',                'date',   '', AF_LOG),

     'location_id'=>        array('Location',          'link',   ATT_DEFFAUL_NULL, AF_READONLY|AF_HIDE_ADD, 'location'),
     'address_formatted'=>  array('Formatted Address', 'text',   '', AF_HIDE_LIST),
     'event_id'=>           array('Event',             'link',   ATT_DEFFAUL_NULL, AF_READONLY|AF_HIDE_ADD, 'event'),

     
  ),
  
  "media_collection_map" => 
  array(
     'id'=>                    array('ID',              'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'created'=>           array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST, 6 ),
//     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE|AF_READONLY, 14 ),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE_ADD, 'site'),
     'user_id'=>           array('User',              'link',  ATT_DEFAULT_USER_ID, AF_SEARCHABLE|AF_HIDE_ADD, 'user'),
     'artist_id'=>         array('Artist',            'link',  ATT_DEFFAUL_NULL, AF_SEARCHABLE|AF_HIDE_ADD, 'user'),
     'curator_id'=>        array('Curator',            'link',  ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_HIDE_ADD, 'user'),

     'active'=>            array('Active',            'bool',   1, 0),
     'rank'=>              array('Rank',              'int', 0, AF_HIDE_ADD, 3),
     'media_collection_id'=> array('Collection',      'link',   '', AF_OBLIGATORY, 'media_collection'),
     'collection_type'   => array('Collection Type', 'link',   0, 0, 'media_collection_type'),
     'media_id'=>            array('Media',           'link',   '', AF_OBLIGATORY, 'media'),
     'product_id'=>          array('Product',         'link',   ATT_DEFAULT_NULL, 0, 'product'),
     'variant_id'=>          array('Variant',         'link',   ATT_DEFAULT_NULL, 0, 'product_variant'),
     'name'=>                array('Name',            'str',   '', AF_SEARCHABLE, 128),
     'original_year'=>       array('Year',            'str',   '', AF_SEARCHABLE, 4),
     'original_technique'=>  array('Technique',       'str',   '', AF_SEARCHABLE, 255),
     'artist_name'=>         array('Artist Name',     'str',   '', AF_SEARCHABLE, 50),
     'curator_name'=>        array('Curator Name',    'str',   '', AF_SEARCHABLE, 50),
  ),

  "gallery" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 8),
     'created'=>           array('Created',           'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   ATT_DEFAULT_NOW, AF_HIDE|AF_READONLY, 14 ),
     'active'=>            array('Active',            'bool',   1, 0),
     'rank'=>              array('Rank',              'int', 0, AF_HIDE_ADD, 3),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE_ADD, 'site'),
     'user_id'=>           array('User',              'link',  ATT_DEFAULT_USER_ID, AF_SEARCHABLE|AF_HIDE_ADD|AF_READONLY, 'user'),
     'parent_id'=>         array('Parent',            'link',   0, AF_READONLY|AF_HIDE_ADD, 'gallery'),
     'title'=>             array('Title',             'str',   '', AF_OBLIGATORY, 255),
     //'title_index'=>       array('Title Image Index', 'int',   0, 0, 3),
     'title_image'=>       array('Title Image',       'link',  ATT_DEFAULT_NULL, 0, 'media'),
     'description'=>       array('Description',       'html',  '', AF_HIDE_LIST),
     'image'            => array('Title image',       'media',     '', 0, $std_image_options),
     'media'            => array('Media',             'media',     '', 0, $gallery_media_options),
     'path'             => array('Path',              'str', 0, AF_HIDE_LIST, 255),
     
  ),
  

  "mail_queue" => 
  array(
     'id'=>                array('ID',            'id',     0, AF_PRIMARY|AF_HIDE_LIST|AF_AUTOINCREMENT, 20),
     'guid'=>              array('GUID',          'uuid',        ATT_DEFAULT_UUID, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 24),
     'parent_id'=>         array('Parent Id',     'parent_id',   ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 11),
     'parent_type'=>       array('Parent Type',   'parent_type', ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD),
     'client_id'=>         array('Client',    		'link',       ATT_DEFAULT_CLIENT_ID, AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>           array('Site',          'link',       ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'user_id' =>          array('User ID',       'link', ATT_DEFAULT_USER_ID, 0, 'user'),     
     'sender_id'=>         array('Sender ID',    	'link',       0, AF_READONLY, 'user'),
     'receiver_id'=>       array('Receiver ID',   'link',       0, AF_READONLY, 'user'),
     'receiver_role'=>     array('Receiver Role', 'str',        '', AF_READONLY, 32),
     'receiver_name'=>     array('Receiver Name', 'str',        '', AF_READONLY, 128),
     'campaign_id' =>      array('Campaign',      'link',    0, 0, 'mail_campaign'),

     'create_time'=>       array('Created',       'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD, 21 ),
     'time_to_send'=>      array('Time to Send',  'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST, 21 ),
     'sent_time'=>         array('Sent',          'datetime',   ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_ADD|AF_READONLY_EDIT, 21 ),
     // 'id_user'=>           array('User',          'link',   1, AF_SEARCHABLE|AF_HIDE_ADD|AF_READONLY_EDIT, 'user'),
     'ip'=>                array('IP',            'ip',    ATT_DEFAULT_CLIENT_IP, AF_HIDE_ADD|AF_READONLY, 20 ),
     'sender'=>            array('Sender',        'str',    '', AF_OBLIGATORY, 50 ),
     'recipient'=>         array('Recipient',     'text',   '', AF_SEARCHABLE|AF_OBLIGATORY),
     'cc'=>                array('CC',            'text',   '', AF_SEARCHABLE),
     'bcc'=>               array('BCC',           'text',   '', AF_SEARCHABLE),
     'replyto'=>           array('Reply-to',      'text',   '', AF_SEARCHABLE),
     'headers'=>           array('Headers',       'text',   '', AF_HIDE_LIST),

     'subject'=>           array('Subject',       'str',  '', AF_OBLIGATORY, 150 ),
     'body'=>              array('Body',          'mail_body',   '', AF_HIDE_LIST|AF_OBLIGATORY),
     'attachment'=>        array('Attachment',    'text',   '', AF_HIDE_LIST),
     'try_sent'=>          array('Try sent',      'int',  0, AF_READONLY|AF_HIDE_ADD|AF_READONLY_EDIT, 6 ),
     'read_count' =>       array('Read Count',    'int',  0, AF_READONLY|AF_HIDE_ADD, 3),
  ),
  
  "mail_campaign" => 
  array(
     'id'=>                array('ID',            'id',     0,  AF_PRIMARY|AF_HIDE_LIST|AF_AUTOINCREMENT, 20),
     'guid'=>              array('GUID',          'uuid',        ATT_DEFAULT_UUID, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 24),
     'parent_id'=>         array('Parent Id',     'parent_id',  ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 11),
     'parent_type'=>       array('Parent Type',   'parent_type',ATT_DEFAULT_NULL, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD),
     'client_id'=>         array('Client',    		'link',       ATT_DEFAULT_CLIENT_ID, AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>           array('Site',          'link',       ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'user_id' =>          array('User ID',       'link',       ATT_DEFAULT_USER_ID, 0, 'user'),
     'sender_id'=>         array('Sender ID',    	'link',       0, AF_READONLY, 'user'),

     'name'=>              array('Name',          'str',    '', AF_SEARCHABLE|AF_OBLIGATORY, 32),
     'description'=>       array('Description',   'text',     '', AF_HIDE_LIST),
     
     'created'=>           array('Created',       'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD, 21 ),
     'time_to_send'=>      array('Time to Send',  'datetime',   ATT_DEFAULT_NULL, AF_HIDE_LIST, 21 ),
     'sent_time'=>         array('Sent',          'datetime',   ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_ADD|AF_READONLY_EDIT, 21 ),

     'receiver_count'=>    array('Receiver Count', 'int',   0, AF_READONLY|AF_HIDE_ADD, 4 ),
     'sent_count' =>       array('Sent Count',     'int',   0, AF_READONLY|AF_HIDE_ADD, 4 ),

     'receiver_roles'=>    array('Receiver Roles', 'text',   '', AF_READONLY),
     'active_since'=>      array('Active Since',   'str',   '', 0, 21),
     
     'filters'=>           array('Filters',       'json',   '', AF_HIDE_LIST),

     'title'=>             array('Title',          'str',    '', AF_SEARCHABLE, 255),
     'sender'=>            array('Sender',        'str',    '', AF_OBLIGATORY, 50 ),
     'recipient'=>         array('Preview Recipient', 'text',   '', AF_SEARCHABLE|AF_OBLIGATORY),
     'recipients'=>        array('Recipients',    'json',   '', AF_HIDE_LIST),
     'failed'=>            array('Failed',        'json',   '', AF_HIDE_LIST),
     'guids'=>             array('GUIDS',         'json',   '', AF_HIDE_LIST),
     'cc'=>                array('CC',            'text',   '', AF_SEARCHABLE),
     'bcc'=>               array('BCC',           'text',   '', AF_SEARCHABLE),
     'replyto'=>           array('Reply-to',      'text',   '', AF_SEARCHABLE),
     'headers'=>           array('Headers',       'text',   '', AF_HIDE_LIST),
     
     'subject'=>           array('Subject',       'str',    '', AF_OBLIGATORY, 255),
     'main_message'=>      array('Message',       'text',   '', AF_HIDE_LIST|AF_OBLIGATORY),
     'template' =>         array('Template',      'str',    '', AF_HIDE_LIST|AF_OBLIGATORY, 255),
     'body'=>              array('Body',          'text',   '', AF_HIDE_LIST),
     'attachment'=>        array('Attachment',    'text',   '', AF_HIDE_LIST),
  ),
     
  "sms_queue" => 
  array(
     'id'=>                array('ID',            'id',       0, AF_PRIMARY|AF_HIDE_LIST|AF_AUTOINCREMENT, 20),
     'guid'=>              array('GUID',          'uuid',        ATT_DEFAULT_UUID, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 24),
     'parent_id'=>         array('Parent Id',     'parent_id',   ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_ADD, 11),
     'parent_type'=>       array('Parent Type',   'parent_type', ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_ADD),
     'site_id'=>           array('Site',          'link',     ATT_DEFAULT_SITE_ID, AF_READONLY, 'site'),
     'client_id'=>         array('Client',    	  'link',     ATT_DEFAULT_CLIENT_ID, AF_READONLY|AF_HIDE, 'client'),
     'create_time'=>       array('Created',       'datetime', ATT_DEFAULT_NOW, AF_READONLY|AF_HIDE_ADD, 21 ),
     'time_to_send'=>      array('Time to Send',  'datetime', ATT_DEFAULT_NOW, 0, 21 ),
     'sent_time'=>         array('Sent',          'datetime', ATT_DEFAULT_NULL, AF_READONLY|AF_HIDE_ADD|AF_READONLY_EDIT, 21 ),
     'user_id'=>           array('User',          'link',     ATT_DEFAULT_USER_ID, AF_SEARCHABLE|AF_HIDE_ADD|AF_READONLY_EDIT, 'user'),
     'session_id'=>        array('Session ID',    'str',      '', AF_SEARCHABLE, 40),
     'ip'=>                array('IP',            'ip',      ATT_DEFAULT_CLIENT_IP, AF_HIDE_ADD|AF_READONLY, 20 ),
     'sender'=>            array('Sender',        'str',      '', AF_OBLIGATORY, 20),
     'recipient'=>         array('Recipient(s)',  'text',     '', AF_SEARCHABLE|AF_OBLIGATORY, 20),
     'body'=>              array('Body',          'text',     '', AF_HIDE_LIST|AF_OBLIGATORY),
     'result' =>           array('Result',        'text',      '', 0, 20),
     'try_sent'=>          array('Try sent',      'int',      0, AF_READONLY|AF_HIDE_ADD|AF_READONLY_EDIT, 6 ),
  ),
  
  "mime_type" =>
  array(
     'extension'=>          array('Extension',          'str',   '', AF_PRIMARY|AF_OBLIGATORY|AF_SEARCHABLE, 20),
     'type'=>               array('Type',               'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 255),
     'subtype'=>            array('Subtype',            'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 50),
     'mime'=>               array('Mime',               'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 50),
     'icon'=>               array('Icon Class',         'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 64),
     'allow_upload' =>      array('Allow upload',       'bool', 0, AF_HIDE_ADD|AF_HIDE_LIST, 1),     
     'description'=>        array('Description',        'str',   '', AF_SEARCHABLE, 200),
  ),
  
  "media" => 
  array(
    'id'                   =>array('ID'            , 'id',   0, AF_PRIMARY|AF_HIDE_LIST|AF_AUTOINCREMENT, 11),
    'created'=>            array('Created',          'datetime',   ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY, 6 ),
    'modified'=>           array('Timestamp',        'timestamp',   0, AF_HIDE|AF_READONLY, 14 ),
    'site_id'            =>array('Site Id'     ,     'link', ATT_DEFAULT_SITE_ID, AF_OBLIGATORY|AF_HIDE_ADD|AF_HIDE_LIST|AF_READONLY, 'site'),
    'client_id'            =>array('Client Id'     , 'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_HIDE_ADD|AF_HIDE_LIST|AF_READONLY, 'client'),
    'parent_id'            =>array('Parent Id'     , 'parent_id', 0, AF_HIDE_ADD|AF_HIDE_LIST|AF_READONLY, 11),
    'parent_type'          =>array('Parent Type'   , 'parent_type', '', AF_HIDE_LIST|AF_READONLY, 30),
    'parent_field'         =>array('Parent Field'  , 'str', 0, AF_HIDE_LIST|AF_READONLY, 100),
    'property_type'        =>array('Property Type' , 'parent_type', 0, AF_HIDE_ADD|AF_HIDE_LIST|AF_READONLY, 30),
    'guid'=>                 array('GUID',           'uuid',        ATT_DEFAULT_UUID, AF_SEARCHABLE|AF_READONLY|AF_HIDE_ADD, 24),
    'source_id'            =>array('Source'        , 'many2one',   0, AF_HIDE_ADD|AF_HIDE_LIST|AF_READONLY, 'source'),
    'city_id'              =>array('City Id'       , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 6),
    'user_id'              =>array('User Id'       , 'link', ATT_DEFAULT_USER_ID, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 'user'),
    'host_id'              =>array('Host ID'       , 'link', 0, AF_HIDE_ADD|AF_READONLY|AF_HIDE_LIST|AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),
    'artist_id'            =>array('Artist Id'     , 'link', ATT_DEFAULT_USER_ID, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 'user'),
    'product_id'           =>array('Product Id'    , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 11),
    'rank'                 =>array('Rank'          , 'int', 0, AF_HIDE_ADD, 3),
    'path'                 =>array('Path'          , 'str', 0, AF_HIDE_LIST, 255),
    'src'                  =>array('Server src'    , 'str', 0, AF_OBLIGATORY|AF_READONLY_EDIT|AF_HIDE_LIST, 255),
    'filename'             =>array('Original File' , 'str', '', AF_OBLIGATORY|AF_READONLY_EDIT, 255),
    'user_filename'        =>array('User File name', 'file', '', AF_OBLIGATORY),

    'name'                 =>array('Name'          , 'str', '', 0, 255),
    'comment'              =>array('Comment'       , 'html', '', 0),
    'short_description'    => array('Short Description', 'str',    '', AF_HIDE_LIST, 200),

    'type'                 =>array('Type'          , 'str', '', AF_READONLY|AF_HIDE_ADD, 20),
    'mime'                 =>array('Mime'          , 'str', '', AF_READONLY|AF_HIDE_ADD, 50),
    'size'                 =>array('File size'     , 'int', 0, AF_HIDE_LIST|AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 11),
  
    'active'               =>array('Active'        , 'bool', 1, AF_HIDE_ADD|AF_HIDE_LIST, 1),
    'missing_file'         =>array('Missing file?' , 'bool', 0, AF_HIDE_ADD|AF_HIDE_LIST, 1),
    'missing_parent'       =>array('Missing parent?' , 'bool', 0, AF_HIDE_ADD|AF_HIDE_LIST, 1),
    'resize'               =>array('Resize?'       , 'bool', 0, AF_HIDE_ADD|AF_HIDE_LIST, 1),
    'resized'              =>array('Resized?'      , 'bool', 0, AF_HIDE_ADD|AF_HIDE_LIST, 1),
    'optimized'            =>array('Optimized?'    , 'bool', 0, AF_READONLY),
    'processed'            =>array('Processed?'    , 'bool', 0, AF_HIDE_LIST, 1),    

    
    'filesize'             =>array('Filesize'      , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 11),

    // image or video
    'height'               =>array('Height'        , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 11),
    'width'                =>array('Width'         , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 11),

    // image
    'depth'                =>array('Bit Depth'     , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 2),
    'exif'                 =>array('Exif'          , 'json', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 2),

    // image/audio/video
    'channels'             =>array('Channels'      , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 2),

    // video    
    'frame_rate'           =>array('Frame rate (fps)' , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 11),
    'video_codec'          =>array('Video Codec' ,  'str', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 50),

    // audio/video    
    'length'               =>array('Length (sec.)' , 'float', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, '6.2'),
    'bit_rate'             =>array('Bit rate (bps)' , 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 11),
    'sample_rate'          =>array('Sample rate (Hz)', 'int', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 11),
    'audio_codec'          =>array('Audio Codec' ,  'str', 0, AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 50),
    
    'url'                  =>array('Url'           , 'str', '', AF_HIDE_ADD|AF_HIDE_LIST, 255),
    'descriptiontype_id'   =>array('Desc.Type'     , 'many2one', '', AF_HIDE_ADD|AF_SEARCHABLE, 'description_type'),
  
    'var1'                 =>array('Var1'          , 'str', '', AF_HIDE_LIST, 50),
    'var2'                 =>array('Var2'          , 'str', '', AF_HIDE_LIST, 50),
    'var3'                 =>array('Var3'          , 'str', '', AF_HIDE_LIST, 50),
    'var4'                 =>array('Var4'          , 'str', '', AF_HIDE_LIST, 50),
                                                                                  
    'original_currency'   => array('Original Currency' , 'valSelect', 'EUR', AF_HIDE_LIST|AF_READONLY_EDIT, $currencyArray),     
    'original_price'      => array('Original price'    , 'money', 0, AF_HIDE_LIST, '8.2'),  
    'original_height'     => array('Original height'   , 'float', 0, AF_HIDE_LIST, '4.1'),    
    'original_width'      => array('Original width'    , 'float', 0, AF_HIDE_LIST, '4.1'),    
    'original_url'        => array('Original url'      , 'url', '', AF_HIDE_LIST, 255),   
    'original_count'      => array('Original count'    , 'int', 0, AF_HIDE_LIST, 4),    
    'original_available'  => array('Original available', 'bool', 0, AF_HIDE_LIST, 4),    
    'original_year'       => array('Original year'     , 'str', '', AF_HIDE_LIST, 4),     
    'original_technique'  => array('Original technique', 'str', '', AF_HIDE_LIST, 255),     

    'digital_currency'    => array('Digital Currency' , 'valSelect', 'EUR', AF_HIDE_LIST|AF_READONLY_EDIT, $currencyArray),     
    'digital_price'       => array('Digital price'     , 'money', 0, AF_HIDE_LIST, '8.2'),  
    'digital_height'      => array('Digital height'    , 'int', 0, AF_HIDE_LIST, 4),    
    'digital_width'       => array('Digital width'     , 'int', 0, AF_HIDE_LIST, 4),    

    'copyright_name'      => array('Copyright name',     'str', '', AF_HIDE_LIST, 128),     
    'copyright_url'       => array('Copyright URL',      'url', '', AF_HIDE_LIST, 255),     
                                                                                
    'cloud_url'       => array('Cloud URL',      'url', '', AF_HIDE_LIST),     
    'cloud_data'       => array('Cloud Data',     'json', '', AF_HIDE_LIST),        
  ),
  
  
  "source" => 
  array(
     'id'                   =>array('ID',                    'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'active'=>            array('Active',            'bool',   0, 0),
     'created'=>           array('Created',           'date',   '', AF_HIDE_LIST, 6 ),
     'timestamp'=>         array('Timestamp',         'timestamp',   0, AF_HIDE_LIST, 6 ),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_READONLY|AF_HIDE_ADD, 'site'),
     'scraped'=>           array('Scraped',          'date',   '', AF_HIDE_LIST, 6 ),
     'name'=>              array('Name',              'str',   '', AF_OBLIGATORY, 100 ),
     'address_street'       => array('Address Street'  , 'str', '', AF_HIDE_LIST, 100),
     'address_postcode'     => array('Address Postcode', 'str', '', AF_HIDE_LIST, 10),
     'address_city'         => array('Address City'    , 'str', '', AF_HIDE_LIST, 50),
     'base_url'=>          array('Base URL',             'url',  '', AF_HIDE_LIST, 100),
     'object_url'=>        array('Object URL',           'url',  '', AF_HIDE_LIST, 100),
     'image_url'=>         array('Image URL',            'url',  '', AF_HIDE_LIST, 100),
     'local_dir'=>         array('Local Dir',            'url',  '', AF_HIDE_LIST, 100),
     'xml_url'=>           array('XML URL',              'url',  '', AF_HIDE_LIST, 100),
  ),
  

  "geoname" => 
  array(
     'id' =>              array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'active'=>           array('Active',            'bool',  0, 0),
     'directory'=>        array('Directory',         'str', 0, AF_OBLIGATORY|AF_SEARCHABLE, 100),
     'name'=>             array('Name',              'str', '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
     'level'=>            array('Level',             'many2one',  0, AF_OBLIGATORY|AF_SEARCHABLE, 'geolevel'),
     'fid'=>              array('Foreign ID',        'int',  0, AF_OBLIGATORY|AF_SEARCHABLE, 11),
     'lang'=>             array('Language',          'str',  '', AF_SEARCHABLE, 2),
     'priority'=>         array('Priority',          'int',  0, 0, 8),
  ),
  
  
  "geolevel" => 
  array(
     'id'=>              array('ID',                  'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 2),
     'name'=>            array('Name',                'str',   '', 1, 20 ),
  ),
  
  
  
  "object_description" => 
  array(
     'id'=>            	    array('ID',                	'id',       '', AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE, 11),
     'parent_type'=>        array('Parent Type',        'parent_type', '', AF_OBLIGATORY, $parentTypeArray),
     'parent_id'=>          array('Parent Id',          'parent_id',      0, AF_OBLIGATORY, 11),
     'site_id' =>           array('Site',               'link',     ATT_DEFAULT_SITE_ID, 0, 'site'),
     'created'=>            array('Created',            'datetime',  ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_HIDE_LIST|AF_READONLY|AF_HIDE_LIST, 6),
     'timestamp'=>          array('Timestamp',          'timestamp',  ATT_DEFAULT_NOW, AF_HIDE|AF_HIDE_ADD|AF_READONLY, 14),
     'user_id'=>            array('Author',             'many2one', ATT_DEFAULT_USER_ID, AF_HIDE_LIST|AF_HIDE_ADD|AF_SEARCHABLE|AF_READONLY, 'user'),
     'machine_translated'=> array('Machine Translated', 'bool',  0, AF_HIDE_ADD|AF_READONLY),
     'language'=>           array('Language',    			  'valSelect', 'en', AF_OBLIGATORY|AF_SEARCHABLE, $langArray),
     'type' =>              array('Desc.Type',          'many2one', 0, AF_SEARCHABLE, 'description_type'),
     'title'=>              array('Title (text)',       'text',     '', AF_HIDE_LIST, 255),
     'description'=>        array('Content (HTML)',     'html',     '', AF_OBLIGATORY|AF_HIDE_LIST),
     'image' =>            array('Image',             'image',      '', AF_HIDE_LIST, 128),
    ),
  
  
  "property_description" => 
  array(
     'id'=>            	    array('ID',                	'id',       '', AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE, 11),
     'property_id'=>        array('Property Id',        'parent_id',      0, AF_READONLY|AF_HIDE_ADD, 11),
     'property_type'=>      array('Property Type',      'parent_type', 0, AF_OBLIGATORY|AF_READONLY|AF_HIDE_ADD, $propertyTypeArray),
     'active'=>            array('Active',             'bool',     1, 0),
     'site_id'=>            array('Site',               'many2one',  '', AF_SEARCHABLE|AF_READONLY_EDIT, 'site'),
//     'owner_id'=>           array('Owner',              'many2one',  '', AF_SEARCHABLE, 'owner'),
     'host_id'=>            array('Host',               'link', 0, AF_HIDE_ADD|AF_READONLY, 'user'),
     'city_id'=>            array('City',               'many2one',  '', AF_SEARCHABLE, 'geo_city'),
     'action' =>            array('Action',             'valSelect',  '', 0, $descriptionActionArray),
  
     //'foo'=>            	  array('Foo',                'str',       '', 0, 50),
  
     'source_id'=>          array('Source',             'link',  '', AF_SEARCHABLE|AF_HIDE_ADD|AF_READONLY, 'source'),
     'created'=>            array('Created',            'datetime',  ATT_DEFAULT_NOW, AF_HIDE_ADD|AF_HIDE_LIST|AF_READONLY|AF_HIDE_LIST, 6),
     'timestamp'=>          array('Timestamp',          'timestamp',  ATT_DEFAULT_NOW, AF_HIDE|AF_HIDE_ADD|AF_READONLY, 14),
     'user_id'=>            array('Author',             'link',     ATT_DEFAULT_USER_ID, AF_HIDE_LIST|AF_HIDE_ADD|AF_SEARCHABLE|AF_READONLY, 'user'),
     'machine_translated'=> array('Machine Translated', 'bool',  0, AF_HIDE_ADD|AF_READONLY),
     'language'=>           array('Language',    			  'valSelect', 'en', AF_OBLIGATORY|AF_SEARCHABLE, $langArray),
     'type' =>              array('Desc.Type',          'many2one', 50, AF_OBLIGATORY|AF_SEARCHABLE, 'description_type'),
     'description'=>        array('Content (HTML)',     'html',     '', AF_OBLIGATORY|AF_HIDE_LIST, 30),
    ),
  
  
  "dictionary" => 
  array(
     'id'=>            	    array('ID',                	'id',       '', AF_PRIMARY|AF_AUTOINCREMENT|AF_HIDE, 11),
     'site_id' =>           array('Site',               'link',     0, 0, 'site'),
     'user_id'=>            array('Author',             'link',     ATT_DEFAULT_USER_ID, AF_HIDE|AF_SEARCHABLE|AF_READONLY, 'user'),
     'machine_translated'=> array('Machine Translated?', 'bool',  0, AF_HIDE|AF_HIDE_ADD|AF_SEARCHABLE|AF_READONLY),

     'language'=>           array('Language',           'many2one',  ATT_DEFAULT_LANG, AF_OBLIGATORY|AF_SEARCHABLE|AF_READONLY_EDIT, 'language'),
     'term'=>            	  array('Term',               'str',       '', AF_OBLIGATORY|AF_SEARCHABLE|AF_READONLY_EDIT, 100),
     'phrase'=>             array('Phrase (HTML)',      'text',     '', AF_OBLIGATORY|AF_HIDE_LIST, 30),

     /** get rid of author */
     //'author'=>             array('Author',             'link',     ATT_DEFAULT_USER_ID, AF_HIDE|AF_SEARCHABLE|AF_READONLY, 'user'),
     'timestamp'=>          array('Timestamp',          'timestamp',     ATT_DEFAULT_NOW, AF_HIDE|AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 14),
     'accessed'=>          array('Last used',          'datetime',     ATT_DEFAULT_NULL, AF_HIDE|AF_HIDE_LIST|AF_HIDE_ADD|AF_READONLY, 14),

    ),
  
  

  "description_type" => 
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
     'private'  =>          array('Private?',            'bool',  0,  0, 0),
     'generic'  =>          array('Generic?',            'bool',  0,  0, 0),
     'description'=>        array('Description',         'text',     '', AF_HIDE_LIST),
  ),
  

  "article_type" => 
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
  ),
  
  
  "billing_period" => 
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'active'=>             array('Active',             'bool',  1, AF_SEARCHABLE, 1),
     'name'=>               array('Name',               'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
  ),
  
  
  "exchange_rate" => 
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'last_updated'=>       array('Timestamp',          'timestamp',     ATT_DEFAULT_NOW, AF_READONLY, 14),
     'from_currency'=>      array('From Currency',      'valSelect', 0, AF_OBLIGATORY, $currencyArray),
     'to_currency'=>        array('To Currency',        'valSelect', 0, AF_OBLIGATORY, $currencyArray),
     'real_rate'=>          array('Bank rate',          'float',    0, AF_READONLY, '8.8'),
     'our_rate'=>           array('Our rate',           'float',    0, AF_READONLY, '8.8'),
     'skim'=>               array('Our commission %',   'float',    0, 0, '2.2'),
  ),
  
  
  "class_group" => 
  array(
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 128),
     'description'=>        array('Description',         'str',   '', AF_HIDE_LIST, 128),
  ),
  
  "class" => 
  array(
     'type'=>            	  array('Type',                'str',   '', AF_PRIMARY, 128),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 128),
     'active'  =>           array('Active?',             'bool',     1,  AF_HIDE_ADD, 0),
     //'site_id'=>            array('Site',                'link', 0, 0, 'site'),
     'user_level'=>         array('User Level',          'many2one',  ATT_DEFAULT_USER_LEVEL, AF_SEARCHABLE|AF_OBLIGATORY, 'user_level'),
     'group'=>              array('Group',               'many2one',  ATT_DEFAULT_USER_LEVEL, AF_SEARCHABLE|AF_OBLIGATORY, 'class_group'),
     'table'=>              array('Table',               'str',   '', 0, 128),
     'key'=>                array('Key',                 'str',   '', 0, 128),
     'flags'=>              array('Flags',               'flags',   0, 0, $__CLASS_FLAGS),
     'descriptor'=>         array('Descriptor',          'str',   '', 0, 128),
     'sort'=>               array('Sort',                'str',   '', 0, 128),
     'parent_class'=>       array('Parent class',        'str',   '', AF_SEARCHABLE, 128),
     'attributes'=>         array('Attributes',          'one2many', 0, 0, 'attribute', 'class'),
  
  ),
  
  
  "attribute" => 
  array(
     'id'=>            	    array('ID',                  'int',   '', AF_PRIMARY|AF_AUTOINCREMENT, 100),
     'field'=>            	array('DB Field',            'str',   '', AF_OBLIGATORY, 100),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
     'class'=>              array('Class',               'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
     'type'=>               array('Type',                'many2one', '', AF_SEARCHABLE, 'attribute_type'),
     'length'=>             array('Length',              'int',   0, 0, 4),
     'flags'=>              array('Flags',               'flags',   0, 0, $__ATTR_FLAGS),
     'default_value'=>      array('Default Value',       'str',   '', 0, 128),
     'relation_class'=>     array('Relation',            'str',   '', 0, 128),
     'relation_filters'=>   array('Filters',             'json',   '', 0),
     'relation_sort'=>      array('Sort',                'str',   '', 0, 128),
//     'args1'=>              array('Arguments 1',         'str',   '', 0, 128),
//     'args2'=>              array('Arguments 2',         'str',   '', 0, 128),
  ),
  
  
  "attribute_type" => 
  array(
//     'id'=>            	    array('ID',                  'int',   '', AF_PRIMARY|AF_AUTOINCREMENT, 100),
     'name'=>            	  array('Type',                'str',   '', AF_PRIMARY, 128),
     'modifier'=>           array('Modifier',            'str',   0, 0, 16),
     'length'=>             array('Length',              'int',   0, 0, 4),
     'db_type'=>            array('DB Type',             'valSelect', '', AF_OBLIGATORY|AF_SEARCHABLE, $db_types),
     'description'=>        array('Description',         'str',   '', AF_SEARCHABLE, 255),
  ),
  
  
  "provider" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
     'active'  =>          array('Active?',           'bool',     1,  AF_HIDE_ADD, 0),
  
     'name'          =>    array('name'         ,    'str',   '', 1, 30 ),
     'provider_id'   =>    array('provider_id'  ,    'str',   '', 1, 20 ),
     'key_required'  =>    array('key_required' ,    'bool',     1,  AF_HIDE_ADD, 0),
     'key_name'      =>    array('key_name'     ,    'str',   '', 1, 10 ),
     'allow_auth'    =>    array('allow_auth'   ,    'bool',     1,  AF_HIDE_ADD, 0),
     'allow_profile' =>    array('allow_profile',    'bool',     1,  AF_HIDE_ADD, 0),
     'allow_contact' =>    array('allow_contact',    'bool',     1,  AF_HIDE_ADD, 0),
     'allow_stream'  =>    array('allow_stream' ,    'bool',     1,  AF_HIDE_ADD, 0),
     'allow_post'    =>    array('allow_post'   ,    'bool',     1,  AF_HIDE_ADD, 0),
     'allow_api'     =>    array('allow_api'    ,    'bool',     1,  AF_HIDE_ADD, 0),
     'url'           =>    array('url'          ,    'str',   '', 1, 50 ),
     'url_reg'       =>    array('url_reg'      ,    'str',   '', 1, 200 ),
     'url_doc'       =>    array('url_doc'      ,    'str',   '', 1, 200 ),
  ),
  
  
  "provider_key" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
     'active'  =>          array('Active?',           'bool',     1,  AF_HIDE_ADD, 0),
     'site_id'=>           array('Site',              'link', 0, 0, 'site'),
     'provider_id'=>       array('Provider',          'link', 0, 0, 'provider'),
     'api_key'=>           array('API Key',           'str',   '', 0, 100 ),
     'api_secret'=>        array('API Secret',        'str',   '', 0, 100 ),
     'scope'=>             array('Scope',             'str',   '', 0, 100 ), // A comma-separated list of permissions you want to request from the user. See the Facebook docs for a full list of available permissions: http://developers.facebook.com/docs/reference/api/permissions.
     'display'=>           array('Display',           'str',   '', 0, 20 ),  // The display context to show the authentication page. Options are: page, popup, iframe, touch and wap. Read the Facebook docs for more details: http://developers.facebook.com/docs/reference/dialogs#display. Default: page
  ),
  
  
  "provider_profile" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
  //         'active'  =>          array('Active?',           'bool',     1,  AF_HIDE_ADD, 0),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
//     'site_id'          => array('Site',              'many2one', 0, AF_OBLIGATORY, 'site'),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_HIDE_LIST|AF_LOG, 'site'),
     'user_id'          => array('User',              'many2one', 0, AF_OBLIGATORY, 'user'),
     'provider_id'      => array('Provider',          'many2one', 0, AF_OBLIGATORY, 'provider'),
     'identifier'       => array('identifier'   ,      'str',      '', 1, 50 ),
     'url_web'          => array('webSiteURL'   ,      'str',      '', 0, 255 ),
     'url_profile'       => array('profileURL'   ,     'str',      '', 0, 255 ),
     'photo'             => array('photoURL'     ,     'str',      '', 0, 255 ),
     'display_name'      => array('displayName'  ,     'str',      '', 0, 50 ),
     'description'      => array('description'  ,      'str',      '', 0, 50 ),
     'first_name'        => array('firstName'    ,     'str',      '', 0, 50 ),
     'last_name'         => array('lastName'     ,     'str',      '', 0, 50 ),
     'gender'           => array('gender'       ,      'str',      '', 0, 10 ),
     'language'         => array('language'     ,      'str',      '', 0, 2 ),
     'age'              => array('age'          ,      'str',      '', 0, 3 ),
     'birth_day'         => array('birthDay'     ,     'str',      '', 0, 2 ),
     'birth_month'       => array('birthMonth'   ,     'str',      '', 0, 2 ),
     'birth_year'        => array('birthYear'    ,     'str',      '', 0, 2 ),
     'email'            => array('email'        ,      'str',      '', 0, 50 ),
     'email_verified'    => array('emailVerified',     'str',      '', 0, 50 ),
     'phone'            => array('phone'        ,      'str',      '', 0, 30 ),
     'address'          => array('address'      ,      'str',      '', 0, 200 ),
     'country'          => array('country'      ,      'str',      '', 0, 2 ),
     'region'           => array('region'       ,      'str',      '', 0, 50 ),
     'city'             => array('city'         ,      'str',      '', 0, 50 ),
     'zip'              => array('zip'          ,      'str',      '', 0, 20 ),
     'friends'          => array('friends'      ,      'json',     ''),
  ),
  
  
  "user_profile" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
  //         'active'  =>          array('Active?',           'bool',     1,  AF_HIDE_ADD, 0),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_HIDE_LIST|AF_LOG, 'site'),
     'client_id'=>         array('Client',    			  'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'rank'=>              array('Rank',               'int',  0, 0, 3),
  
     'user_id'=>           array('User',              'link', 0, AF_OBLIGATORY, 'user'),
     'url_web'          => array('WebSiteURL'   ,      'str',      '', 0, 255 ),
     'photo'            => array('Photo(s)'     ,      'media',     '', 0, $user_media_options),
     'display_name'     => array('Display name'  ,     'str',      '', 0, 50 ),
     'first_name'       => array('First name'    ,     'str',      '', 0, 50 ),
     'last_name'        => array('Last name'     ,     'str',      '', 0, 50 ),
     'gender'           => array('Gender'       ,      'str',      '', 0, 10 ),
     'title'            => array('Title',              'str',      '', 0, 50 ),
     'description'      => array('Description'  ,      'html',     '', 0),
     'interests'        => array('Interests'  ,        'text',     '', 0),
     'location'         => array('Where you live',     'str',      '', 0, 100 ),
     'timezone'         => array('Timezone',           'timezone', '', 0, 32),
     
     'tags'             => array('Tags',               'text',     '', 0),
     'language'         => array('Language'     ,      'str',      '', 0, 2 ),
     'languages'=>         array('Languages',          'json',     '',   AF_HIDE_LIST),
     'age'              => array('Age'          ,      'str',      '', 0, 3 ),
     'birth_day'        => array('Birth day'     ,     'str',      '', 0, 2 ),
     'birth_month'      => array('Birth month'   ,     'str',      '', 0, 2 ),
     'birth_year'       => array('Birth year'    ,     'str',      '', 0, 2 ),
     'date_of_birth'    => array('Date of birth' ,     'date',     '', 0, 2 ),
     'email_address'    => array('Email'        ,      'str',      '', 0, 128 ),
     'email_verified'   => array('Email Verified',     'str',      '', AF_READONLY, 128),     
     'phone'            => array('Phone'        ,      'phone',    '', 0, 30 ),
     'phone_verified'   => array('Phone Verifed',      'str',      '', AF_READONLY, 30),
     'passport'         => array('Passport'        ,   'media',    '', 0, $passport_media_options),
     'passport_verified'=> array('Passport Verifed',   'str',      '', AF_READONLY, 128),
     'mobile'           => array('Mobile'        ,     'str',      '', 0, 30 ),
     'address1'         => array('Address'      ,      'str',      '', 0, 200 ),
     'address2'         => array('Address...',         'str',      '', 0, 200 ),
     'city'             => array('City'         ,      'str',      '', 0, 50 ),
     'zip'              => array('Postal code'  ,      'str',      '', 0, 20 ),
     'state'            => array('State/region',       'str',      '', 0, 50 ),
     'country'          => array('Country'      ,      'many2one', 0, 0, 'countries'),
     'following'        => array('Following'     ,     'int',      0, 0, 6),
     'followers'        => array('Followers'     ,     'int',      0, 0, 6),
     'additional'       => array('Additional fields',  'json',     ''),

     'paypal_id'        => array('PayPal ID',          'str',      '', AF_READONLY, 128),
     'bank_name'=>          array('Bank Name',           'str',  '',  AF_HIDE_LIST, 100),
     'account_name'=>       array('Bank Account Name',   'str',  '',  AF_HIDE_LIST, 100),
     'account_number'=>     array('Bank Account Number', 'str',  '',  AF_HIDE_LIST, 100),
     'account_iban'=>       array('Bank Account IBAN',   'str',  '',  AF_HIDE_LIST, 100),
     'account_routing'=>    array('Bank Account Routing','str',  '',  AF_HIDE_LIST, 100),
     'account_country'=>    array('Bank Account Country','str',  '',  AF_HIDE_LIST, 2),    

     'tax_id'=>              array('Legal/tax id',       'str',   '', AF_HIDE_LIST, 32),
     'commerce_id'=>         array('Business association id',  'str',   '', AF_HIDE_LIST, 32),

     'golf_home_course' => array('Home Course',        'link', 0, 0, 'golf_club'),
     'golf_favorite_course' => array('Favorite Course',        'link', 0, 0, 'golf_club'),
     'golf_handicap'        => array('Handicap'     ,     'int',      0, 0, 6),
     'location_lat'         => array('Latitude'         , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_long'        => array('Longitude'        , 'str','', AF_HIDE_ADD|AF_HIDE_LIST, 24),
     'location_bounds'      =>  array('Bounds',            'json', '', AF_HIDE_ADD|AF_HIDE_LIST),
     'address_formatted'=>  array('Formatted Address', 'text',   '', AF_HIDE_LIST),
     
     
  ),

  "pet_profile" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_EDIT, 14 ),
     'site_id'=>           array('Site',              'link',   ATT_DEFAULT_SITE_ID, AF_HIDE|AF_LOG, 'site'),
     'client_id'=>         array('Client',    			  'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'user_id'=>           array('Owner',             'link', 0, AF_OBLIGATORY|AF_HIDE_ADD|AF_HIDE_EDIT, 'user'),
     'type'=>              array('Type',              'many2one', 0, AF_OBLIGATORY, 'pet_type'),
     'subtype'=>           array('Sub type',          'many2one', 0, 0, 'pet_subtype'),
     'type_text'=>         array('Type (other)',      'str', '', 0, 100),
     'display_name'     => array('Name' ,             'str',      '', AF_OBLIGATORY, 50 ),
     'url_web'          => array('webSiteURL'   ,      'str',      '', 0, 255 ),
     'photo'            => array('photo(s)',           'media',     '', 0, $user_media_options),
     'gender'           => array('gender'       ,      'str',      '', 0, 10 ),
     'description'      => array('description'  ,      'text',     '', 0),
     'age'              => array('age'          ,      'str',      '', 0, 3 ),
     'birth_day'        => array('birth day'     ,      'str',      '', 0, 2 ),
     'birth_month'      => array('birth month'   ,      'str',      '', 0, 2 ),
     'birth_year'       => array('birth year'    ,      'str',      '', 0, 2 ),
  ),

//array('allowed_types' => 'image', 'description_type' => IMAGE_TYPE_PROFILE, 'resize' => true, 'minimum_size' => 640)

  "sharing" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD, 14 ),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>           array('Site',              'many2one',   ATT_DEFAULT_SITE_ID, AF_HIDE_LIST|AF_HIDE_ADD|AF_LOG, 'site'),
     'page_id' =>          array('Page',              'link',        0, AF_HIDE_EDIT|AF_HIDE_ADD, 'site_page'),  
     'user_id'=>           array('User',              'link', ATT_DEFAULT_USER_ID, AF_OBLIGATORY|AF_HIDE_ADD, 'user'),
     'parent_type'      => array('object type',       'str',      ATT_DEFAULT_NULL, AF_HIDE_ADD, 50),
     'parent_id'        => array('object id',        'int',      ATT_DEFAULT_NULL, AF_HIDE_ADD),
     'name'             => array('Name',              'str',      '', 0, 255),
     'title'            => array('Title',             'str',      '', 0, 255),
     'subtitle'         => array('Subtitle',          'str',      '', 0, 128),
     'description'      => array('Description',       'text',     '', AF_HIDE_ADD),
     'language'=>          array('Language',          'many2one',  ATT_DEFAULT_LANG, AF_HIDE_LIST|AF_HIDE_ADD, 'language'),
     'count'            => array('count',             'int',      0, AF_HIDE_ADD),
     'type'             => array('type',              'valSelect', 0, AF_OBLIGATORY, $shareTypeArray),
     'show_title'       => array('Show title?',        'valSelect', 0, AF_HIDE_LIST, $positionArray),
     'share_user_id'=>     array('Sharer',            'link', ATT_DEFAULT_USER_ID, AF_HIDE_ADD, 'user'),
     'image_index'     => array('plugin image index',  'int',      0, AF_HIDE_ADD),
     'style'            => array('style',             'text',     '', 0),
     'link'             => array('link',              'str',      '', AF_HIDE_ADD, 255),
     'size'             => array('size',              'str',      '', AF_HIDE_ADD, 16),

     'plugin_options'   => array('Plugin Options',    'json',     '', AF_HIDE_ADD),
     'popup_options'   => array('Popup Options',    'json',     '', AF_HIDE_ADD),
     /** don't include URL or plug-in will break: change to full_url */
     
     //     'url'              => array('full url',          'str',      '', AF_HIDE_ADD, 255),
     'shorturl'         => array('shorturl',          'str',      '', AF_HIDE_ADD, 50),
     'data'             => array('data',              'text',     '', AF_HIDE_ADD),
     'title_image'      => array('Title image',       'str', 0, AF_HIDE_LIST, 200),
     'container_class'  => array('Container Class',   'str', '', AF_HIDE_LIST, 200),
     'container_tag'  => array('Container Tag',   'str', '', AF_HIDE_LIST, 16),
     'object_tag'  => array('Object Tag',   'str', '', AF_HIDE_LIST, 16),
     'object_class'  => array('Object Class',   'str', '', AF_HIDE_LIST, 200),
  ),

  "plugin" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD, 14 ),
     'client_id'=>         array('Client',    			  'many2one', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>           array('Site',              'many2one',   ATT_DEFAULT_SITE_ID, AF_HIDE_LIST|AF_HIDE_ADD|AF_LOG, 'site'),
     'user_id'=>           array('User',              'link', ATT_DEFAULT_USER_ID, AF_OBLIGATORY|AF_HIDE_ADD, 'user'),
     'share_user_id'=>     array('Shared by',         'link', ATT_DEFAULT_USER_ID, AF_HIDE_ADD, 'user'),
     'parent_type'      => array('object type',       'str',      ATT_DEFAULT_NULL, AF_HIDE_ADD, 50),
     'parent_id'        => array('object id',        'int',      ATT_DEFAULT_NULL, AF_HIDE_ADD),
     'name'             => array('Name',              'str',      '', 0, 255),
     'title'            => array('Title',             'str',      '', 0, 255),
     'subtitle'         => array('Subtitle',          'str',      '', 0, 128),
     'description'      => array('Description',       'text',     '', AF_HIDE_ADD),
     'language'=>          array('Language',          'many2one',  ATT_DEFAULT_LANG, AF_HIDE_LIST|AF_HIDE_ADD, 'language'),
     'count'            => array('count',             'int',      0, AF_HIDE_ADD),
     'type'             => array('type',              'valSelect', 0, AF_OBLIGATORY, $shareTypeArray),
     'show_title'       => array('Show title?',        'valSelect', 0, AF_HIDE_LIST, $positionArray),
     'image_index'     => array('plugin image index',  'int',      0, AF_HIDE_ADD),
     'style'            => array('style',             'text',     '', 0),
     'link'             => array('link',              'str',      '', AF_HIDE_ADD, 255),
     'size'             => array('size',              'str',      '', AF_HIDE_ADD, 16),
     'hover_effect'     => array('hover_effect',      'str',      '', 0, 32),

     'plugin_options'   => array('Plugin Options',    'json',     '', AF_HIDE_ADD),
     'popup_options'   => array('Popup Options',    'json',     '', AF_HIDE_ADD),

     /** don't include URL or plug-in will break: change to full_url */     
     'full_url'         => array('full url',          'str',      '', AF_HIDE_ADD, 255),
     'shorturl'         => array('shorturl',          'str',      '', AF_HIDE_ADD, 50),
     'data'             => array('data',              'text',     '', AF_HIDE_ADD),
     'title_image'      => array('Title image',       'str', 0, AF_HIDE_LIST, 200),
     'container_class'  => array('Container Class',   'str', '', AF_HIDE_LIST, 200),
     'container_tag'  => array('Container Tag',   'str', '', AF_HIDE_LIST, 16),
     'object_tag'  => array('Object Tag',   'str', '', AF_HIDE_LIST, 16),
     'object_class'  => array('Object Class',   'str', '', AF_HIDE_LIST, 200),
  ),
  
  "share_log" => 
  array(
     'id'=>                array('ID',                'id',   0, AF_PRIMARY|AF_AUTOINCREMENT, 3),
     'created'=>           array('Created',           'datetime', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD),
     'timestamp'=>         array('Timestamp',         'timestamp', ATT_DEFAULT_NOW, AF_HIDE_LIST|AF_READONLY|AF_HIDE_ADD, 14 ),

     'client_id'=>         array('Client',    			  'link', ATT_DEFAULT_CLIENT_ID, AF_OBLIGATORY|AF_READONLY|AF_HIDE, 'client'),
     'site_id'=>           array('Target Site',       'link', ATT_DEFAULT_SITE_ID, AF_HIDE_LIST|AF_HIDE_ADD|AF_LOG, 'site'),
     'page_id' =>          array('Target Page',       'link', ATT_DEFAULT_PAGE_ID, AF_HIDE_EDIT|AF_HIDE_ADD, 'site_page'),  
     'user_id'=>           array('Target User',       'link', ATT_DEFAULT_USER_ID, AF_HIDE_ADD, 'user'),

     'sid'=>               array('Share ID',          'str',  '', AF_OBLIGATORY, 20),
     'parent_sid'=>        array('Share parent ID',   'str',  '', 0, 20),

     'source_site_id'=>    array('Source Site',       'link', ATT_DEFAULT_SITE_ID, AF_HIDE_LIST|AF_HIDE_ADD|AF_LOG, 'site'),
     'source_page_id' =>   array('Source Page',       'link', 0, AF_HIDE_EDIT|AF_HIDE_ADD, 'site_page'),  
     'source_user_id'=>    array('Source User',       'link', ATT_DEFAULT_USER_ID, AF_HIDE_EDIT|AF_HIDE_ADD, 'user'),

     'obj_type'         => array('object type',       'str',  ATT_DEFAULT_NULL, AF_HIDE_ADD, 50),
     'obj_id'           => array('object id',         'int',  ATT_DEFAULT_NULL, AF_HIDE_ADD),
                                                      
     'count'            => array('Direct hits',       'int',  0, AF_HIDE_ADD),
     'pcount'           => array('Indirect hits',     'int',  0, AF_HIDE_ADD),
                                                      
     'title'            => array('title',             'str',      '', 0, 255),
     'language'=>          array('Language',          'many2one',  ATT_DEFAULT_LANG, AF_HIDE_LIST|AF_HIDE_ADD, 'language'),
     'url'              => array('url',               'str',      '', AF_HIDE_ADD, 255),
     'referer'          => array('referer',           'str',      '', AF_HIDE_ADD, 255),
     'remote_ip'        => array('IP',                'ip',       ATT_DEFAULT_CLIENT_IP, AF_SEARCHABLE|AF_READONLY, 15 ),
     'remote_cc'        => array('Country Code',      'many2one', ATT_DEFAULT_CLIENT_CC, AF_HIDE_LIST, 'countries'),
     'data'             => array('data',              'json',     '', AF_HIDE_ADD),
  ),
  
  "weekday" =>
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
  ),

  "gender" =>
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
  ),

  "access_token" =>
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'service'=>            array('service',            'str',  'google', AF_OBLIGATORY|AF_SEARCHABLE, 40),
     'account_id'=>         array('account id',         'str',  '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
     'account_name'=>       array('account name',       'str',  '', AF_SEARCHABLE, 100),
     'scope'  =>            array('scope'  ,            'text', '', 0),
     'token'  =>            array('token'  ,            'str',  '', AF_OBLIGATORY|AF_SEARCHABLE, 200),
  ),
  
  "google_application" =>
  array(
     'id'=>            	    array('ID',              'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('name',            'str',  '', AF_OBLIGATORY|AF_SEARCHABLE, 40),
     'api_key'=>            array('API Key',         'str',  '', AF_OBLIGATORY|AF_SEARCHABLE, 40),
     'client_id'=>          array('client id',       'str',  '', AF_OBLIGATORY|AF_SEARCHABLE, 60),
     'client_secret'=>      array('client secret',   'str',  '', AF_OBLIGATORY|AF_SEARCHABLE, 40),
     'redirect_uri'  =>     array('Redirect URI'  ,  'str',  '', AF_OBLIGATORY|AF_SEARCHABLE, 255),
     'scope'  =>            array('scope',           'text', '', 0),
  ),
  
  "password_reset" =>   
  array(
     'id'=>                array('ID',                'id',        0, AF_PRIMARY|AF_AUTOINCREMENT),
     'created'=>           array('Created',           'datetime',  ATT_DEFAULT_NOW, AF_READONLY|AF_HIDE_LIST),
     'expires'=>           array('Expires',           'datetime',  ATT_DEFAULT_NOW, AF_READONLY|AF_HIDE_LIST, 6 ),
     'site_id'=>           array('Site',              'link',      ATT_DEFAULT_SITE_ID, AF_HIDE_LIST|AF_SEARCHABLE|AF_READONLY, 'site'),
     'user_id'=>           array('User',              'link',      ATT_DEFAULT_USER_ID, AF_HIDE_LIST|AF_SEARCHABLE|AF_READONLY, 'user'),
     'used'=>              array('Used?',             'bool',      0, 0),
     'guid'=>              array('Guid',              'str',       '', AF_HIDE_LIST, 40),
  ),

  "default_attributes" =>
  array(
     'id'=>            	    array('ID',                	'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'name'=>               array('Name',                'str',   '', AF_OBLIGATORY|AF_SEARCHABLE, 100),
  ),
  
  "interhome_availability" => 
  array(
     'id'=>            	    array('ID',                  'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'code'=>            	  array('FID',                 'str',   '', AF_OBLIGATORY, 32),
     'created'=>            array('Created',             'date',   '', 0),
     'startdate'=>          array('Start date',          'date',   '', 0),
     'availability'  =>     array('Availability',        'text', '', 0),
     'changeover'  =>       array('Changeover',          'text', '', 0),
     'minstay'  =>          array('Minstay',             'text', '', 0),
     'flexbooking'  =>      array('Flexbooking',         'text', '', 0),
  ),

  "interhome_price" => 
  array(
     'id'=>            	    array('ID',                  'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'code'=>            	  array('FID',                 'str',   '', AF_OBLIGATORY, 32),
     'created'=>            array('Created',             'date',   '', 0),
     'startdate'=>          array('Start date',          'date',   '', 0),
     'enddate'=>            array('End date',            'date',   '', 0),
     'rentalprice'=>        array('Rental price',        'money',   0, AF_HIDE_LIST|AF_READONLY),
     'midweekrentalprice'=> array('Midweek price',       'money',   0, AF_HIDE_LIST|AF_READONLY),
     'weekendrentalprice'=> array('Weekend price',       'money',   0, AF_HIDE_LIST|AF_READONLY),
     'fixprice'=>           array('Fixec price',         'money',   0, AF_HIDE_LIST|AF_READONLY),
  ),
  "interhome_service" => 
  array(
     'id'=>            	    array('ID',                  'id',   '', AF_PRIMARY|AF_AUTOINCREMENT, 11),
     'code'=>            	  array('Code',                'str',   '', AF_OBLIGATORY, 10),
     'accommodationcode'=>  array('FID',                 'str',   '', AF_OBLIGATORY, 32),
     'textcode'=>           array('Text Code',           'str',   '', AF_OBLIGATORY, 6),
     'created'=>            array('Created',             'date',   '', 0),
     'validfrom'=>          array('Valid from',          'date',   '', 0),
     'validto'=>            array('Valid to',            'date',   '', 0),
     'currency'=>           array('Currency',            'valSelect', 0, AF_HIDE_LIST, $currencyArray),
     'serviceprice'=>       array('Service price',       'money',   0, AF_HIDE_LIST|AF_READONLY),
  ),

);
