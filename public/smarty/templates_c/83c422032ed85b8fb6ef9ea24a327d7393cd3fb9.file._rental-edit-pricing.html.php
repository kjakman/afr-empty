<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:05:36
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-edit-pricing.html" */ ?>
<?php /*%%SmartyHeaderCode:683139437551c092aaae4d9-91180298%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '83c422032ed85b8fb6ef9ea24a327d7393cd3fb9' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-edit-pricing.html',
      1 => 1427900736,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '683139437551c092aaae4d9-91180298',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c092ab2f8c7_17045139',
  'variables' => 
  array (
    'scope' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c092ab2f8c7_17045139')) {function content_551c092ab2f8c7_17045139($_smarty_tpl) {?>
                        <form id="property_pricing_form" class="ajax-submit" data-handler="save">
                          <input name="obj_type" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['type'];?>
">
                          <input name="id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
">
                          <h4>Pricing</h4>
                          <div class="form-group">
                              <label>Rate per day</label>
                              <input name="rate_day" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['rate_day'];?>
" type="text" />
                          </div>
                          <div class="form-group">
                              <label>Rate per extra guest</label>
                              <input name="rate_extraperson" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['rate_extraperson'];?>
" type="text" />
                          </div>
                          <div class="form-group">
                              <label>Weekend rate</label>
                              <input name="rate_weekend" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['rate_weekend'];?>
" type="text" />
                          </div>
                          <div class="form-group">
                              <label>Weekly rate</label>
                              <input name="rate_week" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['rate_week'];?>
" type="text" />
                          </div>
                          <div class="form-group">
                              <label>Monthly rate</label>
                              <input name="rate_month" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['rate_month'];?>
" type="text" />
                          </div>
                          <div class="form-group">
                              <label>Security Deposit</label>
                              <input name="security_deposit" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['security_deposit'];?>
" type="text" />
                          </div>
                          <div class="form-group">
                              <label>Cleaning Fee</label>
                              <input name="fee_cleaning" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['fee_cleaning'];?>
" type="text" />
                          </div>
                            <hr>
                            <input type="submit" class="btn btn-primary" value="Save Changes">
                        </form>


<?php }} ?>
