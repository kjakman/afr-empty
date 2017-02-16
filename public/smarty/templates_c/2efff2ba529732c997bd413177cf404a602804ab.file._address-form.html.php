<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:59:30
         compiled from "/web/comps/php/apt-dev/smarty/templates/_address-form.html" */ ?>
<?php /*%%SmartyHeaderCode:117876612551c126c78e2f1-32372653%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '2efff2ba529732c997bd413177cf404a602804ab' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_address-form.html',
      1 => 1427903970,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '117876612551c126c78e2f1-32372653',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c126c7cbf31_44324318',
  'variables' => 
  array (
    'scope' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c126c7cbf31_44324318')) {function content_551c126c7cbf31_44324318($_smarty_tpl) {?>

                              <div class="row">
                                <div class="col-sm-6">
                                  <label>Street</label>
                                  <input name="address1" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['address1'];?>
" type="text" />
                                </div>
                                <div class="col-sm-6">
                                  <label>Line 2</label>
                                  <input name="address2" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['address2'];?>
" type="text" />
                                </div>
                              </div>
                              <div class="row">
                                <div class="col-sm-6">
                                  <label>ZIP/Postal</label>
                                  <input name="zip" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['zip'];?>
" type="text" />
                                </div>
                                <div class="col-sm-6">
                                  <label>City</label>
                                  <input name="city" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['city'];?>
" type="text" />
                                </div>
                              </div>
                              <div class="row">
                                <div class="col-sm-6">
                                  <label>State/Province</label>
                                  <input name="state" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['state'];?>
" type="text" />
                                </div>
                                <div class="col-sm-6">
                                  <label>Country</label>
                                  <input name="country" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['country'];?>
" type="text" />
                                </div>
                              </div>


<?php }} ?>
