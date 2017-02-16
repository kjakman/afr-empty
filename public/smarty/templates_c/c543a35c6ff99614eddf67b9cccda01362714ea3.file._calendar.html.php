<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:05:28
         compiled from "/web/comps/php/apt-dev/smarty/templates/_calendar.html" */ ?>
<?php /*%%SmartyHeaderCode:94504412054dc83a8eddf28-71477865%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'c543a35c6ff99614eddf67b9cccda01362714ea3' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_calendar.html',
      1 => 1427900728,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '94504412054dc83a8eddf28-71477865',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_54dc83a8f15838_00794130',
  'variables' => 
  array (
    'scope' => 0,
    'search' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_54dc83a8f15838_00794130')) {function content_54dc83a8f15838_00794130($_smarty_tpl) {?>
<div id='admincal_full' data-options = '<?php echo json_encode($_smarty_tpl->tpl_vars['scope']->value['cal_params']);?>
'>

  <?php if (($_smarty_tpl->tpl_vars['scope']->value['cal_params']['cal_show']['search'])) {?>
  <?php echo $_smarty_tpl->getSubTemplate ("_calendar-search.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

  <ul class="inline inline-list">
  <?php  $_smarty_tpl->tpl_vars['search'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['search']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['cal_search']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['search']->key => $_smarty_tpl->tpl_vars['search']->value) {
$_smarty_tpl->tpl_vars['search']->_loop = true;
?>
    <li><a href="<?php echo $_smarty_tpl->tpl_vars['search']->value['link'];?>
" data-data='<?php echo json_encode($_smarty_tpl->tpl_vars['search']->value['data']);?>
' class="form-resubmit btn btn-default <?php echo $_smarty_tpl->tpl_vars['search']->value['class'];?>
" 
         data-target="#calendar_search_form"><i class="fa fa-times"></i> <?php echo $_smarty_tpl->tpl_vars['search']->value['name'];?>
</a></li>
  <?php } ?>
  </ul>
  <?php } else { ?>
  <?php }?>
  

  <div class='cal_debug'><?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_params']['debug'];?>
</div>
  <div class='menu_container'><?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_menu'];?>
</div>
  <div id='cal_list'><?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_list'];?>
</div>
  <div id="calendar" unselectable="on" style="-webkit-user-select: none;">
    <!-- foreach i -->
    <div id='admincal-0' class='admincal'>
      <div id='calendar_grid-0' class='cal-container'>
        <div class='cal-guide cell_w_font'><?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_guide'];?>
</div>
        <div class='cal-apts'><?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_properties'];?>
</div>
        <div class='cal-canvas' id='cal_canvas-0' data-index='0' 
             data-size='<?php echo json_encode($_smarty_tpl->tpl_vars['scope']->value['canvas_size']);?>
'
             data-params='<?php echo json_encode($_smarty_tpl->tpl_vars['scope']->value['cal_params']);?>
'>
          <div id='cal_entries-0' class='cal-entries'><?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_reservations'];?>
</div>
          <div id="cal_tip-0"class="cal-tip msg click-close"></div>
        </div>
      </div>
      <div class='cal-footers title_margin canvas_w center'>
      <ul class="month-links"><?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_month_links'];?>
</ul>
      <div class="cal-links"><?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_action_links'];?>
</div>
      </div>
    </div>
    <!-- end foreach -->  
  </div>
</div>
<div id='cal_menu' class='hidden'></div>
<?php echo $_smarty_tpl->getSubTemplate ("_calendar-dialog.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>



<?php }} ?>
