<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:59:19
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-list-item.html" */ ?>
<?php /*%%SmartyHeaderCode:1247756511551ba89c6b9d04-22540699%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'acf51e31c92628466601e95a1ca9547979b9806e' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-list-item.html',
      1 => 1427903959,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1247756511551ba89c6b9d04-22540699',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551ba89c835af5_32324874',
  'variables' => 
  array (
    'rental' => 0,
    'wishlist_id' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551ba89c835af5_32324874')) {function content_551ba89c835af5_32324874($_smarty_tpl) {?>
   <div class="col-md-6 col-lg-4">       
     <div id="shortstay-<?php echo $_smarty_tpl->tpl_vars['rental']->value['id'];?>
" class="air-item listing hilite_target" 
          data-facs="100,130,150,170,230,260,490,621,690,710,730,780,905" 
          data-lat="<?php echo $_smarty_tpl->tpl_vars['rental']->value['location_lat'];?>
" 
          data-lng="<?php echo $_smarty_tpl->tpl_vars['rental']->value['location_long'];?>
" 
          data-name="<?php echo $_smarty_tpl->tpl_vars['rental']->value['name'];?>
" 
          data-url="<?php echo $_smarty_tpl->tpl_vars['rental']->value['link'];?>
" 
          data-user="<?php echo $_smarty_tpl->tpl_vars['rental']->value['host_id'];?>
" 
          data-id="<?php echo $_smarty_tpl->tpl_vars['rental']->value['id'];?>
">
          
        <div class="listing-img media-photo" unselectable="on" style="-webkit-user-select: none;">
          <div class="listing-img-container media-photo image-rotation" data-current="0" 
            data-images='<?php echo json_encode(get_media_sources($_smarty_tpl->tpl_vars['rental']->value['media'],'square'));?>
'>
            <?php if (($_smarty_tpl->tpl_vars['rental']->value['wishlist_data'])) {?>
            <?php $_smarty_tpl->tpl_vars['wishlist_id'] = new Smarty_variable($_smarty_tpl->tpl_vars['rental']->value['wishlist_data']['wishlist_id'], null, 0);?> 
            <div class="abs-top-right pointer ztop margin">
              <a href="#" data-data='<?php echo json_encode($_smarty_tpl->tpl_vars['rental']->value['wishlist_data']);?>
' class="wishlist-link">
                <i class="abs-top-right pointer ztop fa <?php if (($_smarty_tpl->tpl_vars['wishlist_id']->value)) {?>fa-heart<?php } else { ?>fa-heart-o<?php }?> white fa-2x"/>
              </a>
            </div>
            <?php }?>
            <?php if (($_smarty_tpl->tpl_vars['rental']->value['auth_edit'])) {?>
            <div class="abs-top-left pointer ztop margin">
              <a class="btn btn-success btn-xs" target="edit_property" href="/edit-property/<?php echo $_smarty_tpl->tpl_vars['rental']->value['id'];?>
/"><i class="fa fa-pencil"></i></a>
            </div>
            <?php }?>
            <img src="<?php echo get_media_source($_smarty_tpl->tpl_vars['rental']->value['media'],'square');?>
">
          </div>
          <div class="image-rotation-control block-link image-rotation-prev">
            <i class="icon icon-chevron-left listing-slideshow-chevron">&lt;</i>
          </div>
          <div class="image-rotation-control block-link image-rotation-next">
            <i class="icon icon-chevron-right listing-slideshow-chevron">&gt;</i>
          </div>
        </div>
        <div class="listing-footer clearfix">
          <a class="listing-host-img media-link media-photo" href="/profile/501/">
            <img src="http://test.hitabrick.com/user/501/upload/object/user_profile/1170/photo/image/small/passfoto.png">
          </a>
          <a class="listing-quick-info property-detail-link" href="/serviced-apartment/<?php echo $_smarty_tpl->tpl_vars['rental']->value['shortname'];?>
/" title="Entire home | Quinta do Lago, Portugal">
            <span class="listing-room-type">
              <?php echo $_smarty_tpl->tpl_vars['rental']->value['name'];?>
<br>
              <?php echo $_smarty_tpl->tpl_vars['rental']->value['address_city'];?>
<br>
              <?php if (($_smarty_tpl->tpl_vars['rental']->value['book_direct'])) {?><i class="fa fa-bolt red"></i> Book Direct<br><?php }?>
            </span>
          </a>
          
          <a class="listing-price property-detail-link" href="/serviced-apartment/<?php echo $_smarty_tpl->tpl_vars['rental']->value['shortname'];?>
/">
            <span class="price">
              <span class="currency"><?php echo currency2html($_smarty_tpl->tpl_vars['rental']->value['currency']);?>
</span>
              <span class="price-amount"><?php echo round($_smarty_tpl->tpl_vars['rental']->value['rate_day']);?>
</span>
            </span>
            <span class="price-sub">
                Per night
            </span>
            <input type="number" readonly class="rating" 
             value="<?php echo $_smarty_tpl->tpl_vars['rental']->value['review_score'];?>
"
             data-min="0" data-max="10"
             data-size="xxs" data-show-clear="false"
             data-show-caption="false">
          </a>
        </div>
      </div>
    </div>


<?php }} ?>
