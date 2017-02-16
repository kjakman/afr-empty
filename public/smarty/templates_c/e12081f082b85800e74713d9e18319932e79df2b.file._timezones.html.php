<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:06:01
         compiled from "/web/comps/php/apt-dev/smarty/templates/_timezones.html" */ ?>
<?php /*%%SmartyHeaderCode:1423432567551c174cc0b3f8-50951171%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'e12081f082b85800e74713d9e18319932e79df2b' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_timezones.html',
      1 => 1427904361,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1423432567551c174cc0b3f8-50951171',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c174cc765b8_60567114',
  'variables' => 
  array (
    'timezones' => 0,
    'group' => 0,
    'zone' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c174cc765b8_60567114')) {function content_551c174cc765b8_60567114($_smarty_tpl) {?><?php if (!is_callable('smarty_function_json')) include '/usr/share/php/Smarty/plugins/function.json.php';
?>
<?php echo smarty_function_json(array('file'=>"afr/json/timezones.json",'assign'=>"timezones"),$_smarty_tpl);?>

<?php  $_smarty_tpl->tpl_vars['group'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['group']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['timezones']->value; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['group']->key => $_smarty_tpl->tpl_vars['group']->value) {
$_smarty_tpl->tpl_vars['group']->_loop = true;
?>
  <?php $_smarty_tpl->tpl_vars['name'] = new Smarty_variable($_smarty_tpl->tpl_vars['group']->value['name'], null, 0);?>
  <?php  $_smarty_tpl->tpl_vars['zone'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['zone']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['group']->value['zones']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['zone']->key => $_smarty_tpl->tpl_vars['zone']->value) {
$_smarty_tpl->tpl_vars['zone']->_loop = true;
?>
    <option value="<?php echo $_smarty_tpl->tpl_vars['zone']->value['value'];?>
" data-alternative-spellings="<?php echo $_smarty_tpl->tpl_vars['zone']->value['name'];?>
"><?php echo $_smarty_tpl->tpl_vars['zone']->value['value'];?>
</option>
  <?php } ?>
<?php } ?>

<?php }} ?>
