<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:20:55
         compiled from "/web/comps/php/apt-dev/smarty/templates/_credit-card-form.html" */ ?>
<?php /*%%SmartyHeaderCode:1560204791551c126c71ccf8-69542873%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '40792b57bf23702f7c75c06355ce9141ae7f8042' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_credit-card-form.html',
      1 => 1427905255,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1560204791551c126c71ccf8-69542873',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c126c7879d5_92980153',
  'variables' => 
  array (
    'user' => 0,
    'site' => 0,
    'dummy' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c126c7879d5_92980153')) {function content_551c126c7879d5_92980153($_smarty_tpl) {?>

  
                            <input name="user_id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['user']->value['id'];?>
" />
                            <input name="site_id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['site']->value['id'];?>
" />
                            <input name="cc_type_name" type="hidden" <?php if (($_smarty_tpl->tpl_vars['dummy']->value)) {?>value="visa"<?php }?>/>
                            <div class="clearfix">
                                <div class="form-group form-group-cc-number">
                                    <label>Card Number</label>
                                    <input name="cc_number" class="form-control" placeholder="xxxx xxxx xxxx xxxx" type="text" <?php if (($_smarty_tpl->tpl_vars['dummy']->value)) {?>value="4020022411122767"<?php }?>/><span class="cc-card-icon"></span>
                                </div>
                                <div class="form-group form-group-cc-cvc">
                                    <label>CVC</label>
                                    <input name="cc_cvv2" class="form-control" placeholder="xxxx" type="text" <?php if (($_smarty_tpl->tpl_vars['dummy']->value)) {?>value="000"<?php }?>/>
                                </div>
                            </div>
                            <div class="clearfix">
                                <div class="form-group form-group-cc-name">
                                    <label>Cardholder Name</label>
                                    <input name="cc_cardholder" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['user']->value['full_name'];?>
" type="text" <?php if (($_smarty_tpl->tpl_vars['dummy']->value)) {?>value="Dummy Card"<?php }?>/>
                                </div>
                                <div class="form-group form-group-cc-date">
                                    <label>Valid Thru</label>
                                    <input name="cc_exp" class="form-control" placeholder="mm/yy" type="text" <?php if (($_smarty_tpl->tpl_vars['dummy']->value)) {?>value="12 / 19"<?php }?>/>
                                </div>
                            </div>
                            
                            


<?php }} ?>
