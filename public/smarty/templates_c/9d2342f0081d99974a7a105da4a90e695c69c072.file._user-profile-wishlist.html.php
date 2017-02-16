<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:20:56
         compiled from "/web/comps/php/apt-dev/smarty/templates/_user-profile-wishlist.html" */ ?>
<?php /*%%SmartyHeaderCode:1854243093551c1ae8df0ab5-85716610%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '9d2342f0081d99974a7a105da4a90e695c69c072' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_user-profile-wishlist.html',
      1 => 1427905256,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1854243093551c1ae8df0ab5-85716610',
  'function' => 
  array (
  ),
  'variables' => 
  array (
    'scope' => 0,
    'wishlistitem' => 0,
    'wishlistitem_id' => 0,
  ),
  'has_nocache_code' => false,
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c1ae8ef5e22_36819405',
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c1ae8ef5e22_36819405')) {function content_551c1ae8ef5e22_36819405($_smarty_tpl) {?><?php if (!is_callable('smarty_modifier_date_format')) include '/usr/share/php/Smarty/plugins/modifier.date_format.php';
?>

                    <ul class="booking-list booking-list-wishlist">
                        <?php  $_smarty_tpl->tpl_vars['wishlistitem'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['wishlistitem']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['wishlist']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['wishlistitem']->key => $_smarty_tpl->tpl_vars['wishlistitem']->value) {
$_smarty_tpl->tpl_vars['wishlistitem']->_loop = true;
?>
                          <?php $_smarty_tpl->tpl_vars['wishlistitem_id'] = new Smarty_variable($_smarty_tpl->tpl_vars['wishlistitem']->value['id'], null, 0);?>
                        <li id="wishlist-item-<?php echo $_smarty_tpl->tpl_vars['wishlistitem_id']->value;?>
"><span class="booking-item-wishlist-title"><i class="fa fa-home"></i> vacation rental <span >added on <?php echo smarty_modifier_date_format($_smarty_tpl->tpl_vars['wishlistitem']->value['created']);?>
</span></span>
                        
                            <a class="fa fa-times booking-item-wishlist-remove delete-object" href="#" rel="tooltip"
                              data-obj_type="wishlist" data-obj_id="<?php echo $_smarty_tpl->tpl_vars['wishlistitem']->value['id'];?>
" 
                              data-handler="delete_object_handler" 
                              data-handler_data='<?php echo json_encode(array("target"=>"#wishlist-item-".((string)$_smarty_tpl->tpl_vars['wishlistitem_id']->value)));?>
'
                              data-placement="top" title="remove from wishlist"></a>
                            <a class="booking-item" href="<?php echo smarty_property_link($_smarty_tpl->tpl_vars['wishlistitem']->value['obj']);?>
">
                                <div class="row">
                                    <div class="col-md-3">
                                        <div class="booking-item-img-wrap">
                                            <img src="<?php echo return_if_empty(get_media_source($_smarty_tpl->tpl_vars['wishlistitem']->value['obj']['media'],'small'),'/traveler/img/800x600.png');?>
" alt="Image Alternative text" title="hotel 2" />
                                            <div class="booking-item-img-num"><i class="fa fa-picture-o"></i>6</div>
                                        </div>
                                    </div>
                                    <div class="col-md-6">
                                        <div class="booking-item-rating">
                                        <input type="number" readonly class="rating" 
                                               value="<?php echo $_smarty_tpl->tpl_vars['wishlistitem']->value['obj']['review_score'];?>
" 
                                               min=0 max=10
                                               data-size="xss" data-glyphicon="false" data-show-clear="false"                                       
                                               data-show-caption="false">

                                        <span class="booking-item-rating-number"><b ><?php echo round(($_smarty_tpl->tpl_vars['wishlistitem']->value['obj']['review_score']/2),"1");?>
</b> of 5</span><small>(<?php echo $_smarty_tpl->tpl_vars['wishlistitem']->value['obj']['review_nr'];?>
 reviews)</small>
                                        </div>
                                        <h5 class="booking-item-title"><?php echo $_smarty_tpl->tpl_vars['wishlistitem']->value['obj']['name'];?>
</h5>
                                        <p class="booking-item-address"><i class="fa fa-map-marker"></i> <?php echo $_smarty_tpl->tpl_vars['wishlistitem']->value['obj']['address_city'];?>
</p>
                                        <ul class="booking-item-features booking-item-features-rentals booking-item-features-sign">
                                            <li rel="tooltip" data-placement="top" title="Sleeps"><i class="fa fa-male"></i><span class="booking-item-feature-sign">x 5</span>
                                            </li>
                                            <li rel="tooltip" data-placement="top" title="Bedrooms"><i class="im im-bed"></i><span class="booking-item-feature-sign">x 2</span>
                                            </li>
                                            <li rel="tooltip" data-placement="top" title="Bathrooms"><i class="im im-shower"></i><span class="booking-item-feature-sign">x 2</span>
                                            </li>
                                        </ul>
                                    </div>
                                    <div class="col-md-3">
                                        <span class="booking-item-price"><?php echo currency2html($_smarty_tpl->tpl_vars['wishlistitem']->value['obj']['currency']);?>
<?php echo round($_smarty_tpl->tpl_vars['wishlistitem']->value['obj']['rate_day']);?>
</span>
                                        <span>/night</span>
                                        
                                        <span class="btn btn-primary">Book Now</span>                                        
                                    </div>
                                </div>
                            </a>
                        </li>
                        <?php } ?>
                    </ul>


<?php }} ?>
