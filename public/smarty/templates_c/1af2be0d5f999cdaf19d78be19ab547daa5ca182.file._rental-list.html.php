<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:59:19
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-list.html" */ ?>
<?php /*%%SmartyHeaderCode:694092881551a945bbe1cf3-42289765%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '1af2be0d5f999cdaf19d78be19ab547daa5ca182' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-list.html',
      1 => 1427903959,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '694092881551a945bbe1cf3-42289765',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551a945bc87247_03436248',
  'variables' => 
  array (
    'scope' => 0,
    'filter' => 0,
    'site' => 0,
    'tip' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551a945bc87247_03436248')) {function content_551a945bc87247_03436248($_smarty_tpl) {?>
<?php echo $_smarty_tpl->tpl_vars['scope']->value['message'];?>

<?php if (($_smarty_tpl->tpl_vars['scope']->value['rentals'])) {?> 
  <?php echo $_smarty_tpl->tpl_vars['scope']->value['count'];?>
 Rentals <?php if ((count($_smarty_tpl->tpl_vars['scope']->value['rentals'])<$_smarty_tpl->tpl_vars['scope']->value['count'])) {?>(Showing first <?php echo count($_smarty_tpl->tpl_vars['scope']->value['rentals']);?>
)<?php }?>
  <ul class="inline inline-list">
  <?php  $_smarty_tpl->tpl_vars['filter'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['filter']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['filters']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['filter']->key => $_smarty_tpl->tpl_vars['filter']->value) {
$_smarty_tpl->tpl_vars['filter']->_loop = true;
?>
    <li><a href="<?php echo $_smarty_tpl->tpl_vars['filter']->value['link'];?>
" data-data='<?php echo json_encode($_smarty_tpl->tpl_vars['filter']->value['data']);?>
' class="form-resubmit btn btn-default <?php echo $_smarty_tpl->tpl_vars['filter']->value['class'];?>
" 
         data-target="#rental_search_form"><i class="fa fa-times"></i> <?php echo $_smarty_tpl->tpl_vars['filter']->value['name'];?>
</a></li>
  <?php } ?>
  </ul>

  <div id="rental_list" data-count="<?php echo $_smarty_tpl->tpl_vars['scope']->value['count'];?>
" data-id_list="<?php echo $_smarty_tpl->tpl_vars['scope']->value['id_list'];?>
" 
       data-property_type="<?php echo $_smarty_tpl->tpl_vars['site']->value['property_type'];?>
" class="row margin-top">
  <?php  $_smarty_tpl->tpl_vars['rental'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['rental']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['rentals']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['rental']->key => $_smarty_tpl->tpl_vars['rental']->value) {
$_smarty_tpl->tpl_vars['rental']->_loop = true;
?>
  <?php echo $_smarty_tpl->getSubTemplate ("_rental-list-item.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

  <?php } ?> 
  </div>
<?php } else { ?>
  <h3>We're sorry...</h3>
  <p class="bold">We could not find any properties that matched your search</p> 
  <ul>
  <?php  $_smarty_tpl->tpl_vars['tip'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['tip']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['tips']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['tip']->key => $_smarty_tpl->tpl_vars['tip']->value) {
$_smarty_tpl->tpl_vars['tip']->_loop = true;
?>
    <li><a href="<?php echo $_smarty_tpl->tpl_vars['tip']->value['link'];?>
" data-data='<?php echo json_encode($_smarty_tpl->tpl_vars['tip']->value['data']);?>
' class="<?php echo return_if_empty($_smarty_tpl->tpl_vars['tip']->value['class'],'form-resubmit');?>
" 
         data-target = "#rental_search_form"><?php echo $_smarty_tpl->tpl_vars['tip']->value['name'];?>
</a></li>
  <?php } ?>
  </ul>
<?php }?>
<?php echo $_smarty_tpl->tpl_vars['scope']->value['debug'];?>


<?php }} ?>
