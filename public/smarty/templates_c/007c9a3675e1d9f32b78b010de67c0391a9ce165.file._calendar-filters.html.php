<?php /* Smarty version Smarty-3.1.20, created on 2015-02-20 07:46:38
         compiled from "/web/comps/php/apt-dev/smarty/templates/_calendar-filters.html" */ ?>
<?php /*%%SmartyHeaderCode:36653625054e1abdf670055-86275621%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '007c9a3675e1d9f32b78b010de67c0391a9ce165' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_calendar-filters.html',
      1 => 1424436398,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '36653625054e1abdf670055-86275621',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_54e1abdf69da31_21572475',
  'variables' => 
  array (
    'root_user' => 0,
    'scope' => 0,
    'site' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_54e1abdf69da31_21572475')) {function content_54e1abdf69da31_21572475($_smarty_tpl) {?><?php if (!is_callable('smarty_function_html_options')) include '/usr/share/php/Smarty/plugins/function.html_options.php';
?>
<!-- automatically generated on 2015-02-20 07:46:38. DO NOT EDIT -->
            <form id="calendar-filter-form" class="ajax-submit form-horizontal" data-handler="search" data-success_handler="cal_search_handler">
              <?php if (($_smarty_tpl->tpl_vars['root_user']->value)) {?>
              Root
              <?php echo smarty_function_html_options(array('name'=>'client_id','options'=>$_smarty_tpl->tpl_vars['scope']->value['cal_params']['clients'],'selected'=>$_smarty_tpl->tpl_vars['scope']->value['cal_params']['filters']['client_id']),$_smarty_tpl);?>
              
              <?php } else { ?>
              Not root
              <input name="client_id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['site']->value['client_id'];?>
" />
              <input name="legal_entity_id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['site']->value['legal_entity_id'];?>
" />
              <?php }?>
              <?php echo count($_smarty_tpl->tpl_vars['scope']->value['cal_params']['apts']);?>
 apts: 
              <?php echo smarty_function_html_options(array('name'=>'id','options'=>$_smarty_tpl->tpl_vars['scope']->value['cal_params']['apts'],'selected'=>$_smarty_tpl->tpl_vars['scope']->value['cal_params']['filters']['apt_id']),$_smarty_tpl);?>
              

              <?php echo count($_smarty_tpl->tpl_vars['scope']->value['cal_params']['hosts']);?>
 hosts: 
              <?php echo smarty_function_html_options(array('name'=>'host_id','options'=>$_smarty_tpl->tpl_vars['scope']->value['cal_params']['hosts'],'selected'=>$_smarty_tpl->tpl_vars['scope']->value['cal_params']['filters']['host_id']),$_smarty_tpl);?>
              
              <input name="search" type="hidden" value="post" />
              <input name="obj_type" type="hidden" value="property" />
              <input name="active" type="hidden" value="1" />
              <input name="fields" type="hidden" value="property.id" />
              <!--input name="format" type="hidden" value="list" /-->
              <input type="submit" class="btn btn-primary" value="Search">              
              <input type="submit" class="btn btn-danger reset-form-submit" value="Reset">              
            </form>


<?php }} ?>
