<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:59:41
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-review-item.html" */ ?>
<?php /*%%SmartyHeaderCode:63673745551ba8d8c354c9-03306975%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '885b5970302e4a53b97d1c9dd91b47378265cf2e' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-review-item.html',
      1 => 1427903981,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '63673745551ba8d8c354c9-03306975',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551ba8d8ef9e61_66427810',
  'variables' => 
  array (
    'review' => 0,
    'global' => 0,
    'compact' => 0,
    'name' => 0,
    'k' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551ba8d8ef9e61_66427810')) {function content_551ba8d8ef9e61_66427810($_smarty_tpl) {?><?php if (!is_callable('smarty_modifier_truncate')) include '/usr/share/php/Smarty/plugins/modifier.truncate.php';
if (!is_callable('smarty_modifier_date_format')) include '/usr/share/php/Smarty/plugins/modifier.date_format.php';
?>
                                <div class="row">
                                    <div class="col-md-2">
                                        <div class="booking-item-review-person">
                                            <a class="booking-item-review-person-avatar round" href="#">
                                                <img src="/traveler/img/70x70.png" alt="Image Alternative text" title="Bubbles" />
                                            </a>
                                            <p class="booking-item-review-person-name"><a href="/profile/<?php echo $_smarty_tpl->tpl_vars['review']->value['guest_id'];?>
"><?php echo $_smarty_tpl->tpl_vars['review']->value['first_name'];?>
 <?php echo $_smarty_tpl->tpl_vars['review']->value['last_name'];?>
</a>
                                            </p>
                                            <p class="booking-item-review-person-loc"><?php echo $_smarty_tpl->tpl_vars['review']->value['city'];?>
, <?php echo $_smarty_tpl->tpl_vars['review']->value['country'];?>
</p>
                                        </div>
                                    </div>
                                    <div class="col-md-10">
                                        <div class="booking-item-review-content">
                                            <?php if (($_smarty_tpl->tpl_vars['review']->value['feedback_title'])) {?><h5 class="inline-block">"<?php echo $_smarty_tpl->tpl_vars['review']->value['feedback_title'];?>
"</h5><?php }?>
                                            <input type="number" readonly class="rating"
                                               value="<?php echo round($_smarty_tpl->tpl_vars['review']->value['feedback_overall']);?>
" 
                                               data-size="xs" data-show-clear="false"
                                                   data-min=0 data-max=10
                                                   data-star-captions='<?php echo json_encode($_smarty_tpl->tpl_vars['global']->value['rating_captions']);?>
',
                                                   data-star-caption-classes='<?php echo json_encode($_smarty_tpl->tpl_vars['global']->value['rating_classes']);?>
',
                                               
                                               data-show-caption="true">
                                            <?php if (($_smarty_tpl->tpl_vars['compact']->value)) {?> 
                                            <div class="booking-item-review-stripped-content">
                                            <?php echo smarty_modifier_truncate(preg_replace('!<[^>]*?>!', ' ', $_smarty_tpl->tpl_vars['review']->value['feedback_comments']),160,"...");?>

                                            </div>
                                            <?php }?>
                                            <div class="booking-item-review-more-content">
                                              <?php echo $_smarty_tpl->tpl_vars['review']->value['feedback_comments'];?>

                                                <p class="text-small mt20">Stayed <?php echo smarty_modifier_date_format($_smarty_tpl->tpl_vars['review']->value['checkout'],"%B %Y");?>
, <?php echo smarty_get_object($_smarty_tpl->tpl_vars['review']->value['profile'],"feedback_profile","name");?>
 (<?php echo smarty_get_object($_smarty_tpl->tpl_vars['review']->value['purpose'],"feedback_purpose","name");?>
)</p>
                                                <div class="clearfix">
                                                   <?php  $_smarty_tpl->tpl_vars['name'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['name']->_loop = false;
 $_smarty_tpl->tpl_vars['k'] = new Smarty_Variable;
 $_from = $_smarty_tpl->tpl_vars['global']->value['rating_keys']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['name']->key => $_smarty_tpl->tpl_vars['name']->value) {
$_smarty_tpl->tpl_vars['name']->_loop = true;
 $_smarty_tpl->tpl_vars['k']->value = $_smarty_tpl->tpl_vars['name']->key;
?>                                               
                                                    <div class="float-left margin-right">
                                                        <div class="booking-item-raiting-list-title"><?php echo $_smarty_tpl->tpl_vars['name']->value;?>
 (<?php echo $_smarty_tpl->tpl_vars['review']->value[$_smarty_tpl->tpl_vars['k']->value];?>
)</div>
                                                        <input type="number" readonly class="rating"
                                                           value="<?php echo round($_smarty_tpl->tpl_vars['review']->value[$_smarty_tpl->tpl_vars['k']->value]);?>
" 
                                                           data-min=0 data-max=10
                                                           data-star-captions='<?php echo json_encode($_smarty_tpl->tpl_vars['global']->value['rating_captions']);?>
',
                                                           data-star-caption-classes='<?php echo json_encode($_smarty_tpl->tpl_vars['global']->value['rating_classes']);?>
',
                                                           
                                                           data-size="xs" data-show-clear="false"
                                                           data-show-caption="false"> 
                                                    </div>
                                                    
                                                <?php } ?>
                                                </div>
                                            </div>
                                            <?php if (($_smarty_tpl->tpl_vars['compact']->value)) {?> 
                                            <div class="booking-item-review-expand">
                                              <span class="booking-item-review-expand-more">More <i class="fa fa-angle-down"></i></span><span class="booking-item-review-expand-less">Less <i class="fa fa-angle-up"></i></span>
                                            </div>
                                            <p class="booking-item-review-rate">Was this review helpful?
                                                <a class="fa fa-thumbs-o-up box-icon-inline round helpful-link" href="#" data-obj_type="feedback" data-obj_id="<?php echo $_smarty_tpl->tpl_vars['review']->value['id'];?>
"></a> <b class="text-color helpful-count"><?php echo return_if_empty($_smarty_tpl->tpl_vars['review']->value['helpful'],"0");?>
</b>
                                            </p>
                                            <?php }?>
                                        </div>
                                    </div>
                                </div>

<?php }} ?>
