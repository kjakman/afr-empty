<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:20:55
         compiled from "/web/comps/php/apt-dev/smarty/templates/_credit-card.html" */ ?>
<?php /*%%SmartyHeaderCode:1041018921551c174203be88-88494750%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'adebaf3dbd868c3579922a74344f04c2b821ae7e' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_credit-card.html',
      1 => 1427905255,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1041018921551c174203be88-88494750',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c17420d4f77_10071555',
  'variables' => 
  array (
    'card' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c17420d4f77_10071555')) {function content_551c17420d4f77_10071555($_smarty_tpl) {?>
                        <div class="col-md-4" id="card-<?php echo $_smarty_tpl->tpl_vars['card']->value['id'];?>
" >
                            <div class="card-thumb">
                                <ul class="card-thumb-actions">
                                    <li>
                                        <a class="fa fa-pencil popup-text" href="#edit-card-dialog" rel="tooltip" data-placement="top" title="edit" data-effect="mfp-zoom-out"></a>
                                    </li>
                                    <li>
                                        <a class="fa fa-times" href="#" id="delete-<?php echo $_smarty_tpl->tpl_vars['card']->value['id'];?>
" 
                                            data-toggle="confirmation" data-on-confirm="delete_object" 
                                            data-obj_type="cc" data-id="<?php echo $_smarty_tpl->tpl_vars['card']->value['id'];?>
" data-handler="delete_object_handler" 
                                            data-handler_data=' { "target": "#card-<?php echo $_smarty_tpl->tpl_vars['card']->value['id'];?>
" } ' 
                                            rel="tooltip" data-placement="top" title="remove">
                                        </a>
                                    </li>
                                </ul>
                                <p class="card-thumb-number"><?php echo $_smarty_tpl->tpl_vars['card']->value['number'];?>
</p>
                                <p class="<?php if (($_smarty_tpl->tpl_vars['card']->value['expired'])) {?>text-danger<?php } else { ?>card-thumb-valid<?php }?>">valid thru <span><?php echo $_smarty_tpl->tpl_vars['card']->value['exp_month'];?>
 / <?php echo $_smarty_tpl->tpl_vars['card']->value['exp_year'];?>
</span><?php if (($_smarty_tpl->tpl_vars['card']->value['expired'])) {?> <span>(Expired)</span><?php }?>
                                </p>
                                <img class="card-thumb-type" src="<?php echo $_smarty_tpl->tpl_vars['card']->value['image'];?>
" alt="Image Alternative text" title="Image Title" /><small>cardholder name</small>
                                <h5 class="uc"><?php echo $_smarty_tpl->tpl_vars['card']->value['cardholder'];?>
</h5>
                            </div>
                        </div>


<?php }} ?>
