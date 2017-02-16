<?php /* Smarty version Smarty-3.1.20, created on 2015-03-31 16:50:49
         compiled from "/web/comps/php/apt-dev/smarty/templates/_calendar-search.html" */ ?>
<?php /*%%SmartyHeaderCode:105833779254eb01ae74f915-70939586%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '6834488b6b3e9dc9bad2e316ccbc28ac1d82daf5' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_calendar-search.html',
      1 => 1427820648,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '105833779254eb01ae74f915-70939586',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_54eb01ae7f1632_99387754',
  'variables' => 
  array (
    'site' => 0,
    'scope' => 0,
    'client' => 0,
    'host' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_54eb01ae7f1632_99387754')) {function content_54eb01ae7f1632_99387754($_smarty_tpl) {?>
  <form id="calendar_search_form" class="ajax-submit" action="/calendar/" data-handler="calendar-search" data-success_handler="calendar_search_handler">

    <input type="hidden" name="site_id" value="<?php echo $_smarty_tpl->tpl_vars['site']->value['id'];?>
" />
    <input type="hidden" name="t" value="<?php echo return_if_empty($_smarty_tpl->tpl_vars['scope']->value['cal_params']['property_type'],'shortstay');?>
" />

    <?php if ((count($_smarty_tpl->tpl_vars['scope']->value['cal_params']['clients']))) {?>
    <div class="col-md-2 relative nogutter">
      <select class="form-control" id="client_id" name="client_id">
        <option <?php if ((!$_smarty_tpl->tpl_vars['scope']->value['cal_params']['cal_search']['client_id'])) {?> selected="selected"<?php }?> value="0">All Clients</option>
        <?php  $_smarty_tpl->tpl_vars['client'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['client']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['cal_params']['clients']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['client']->key => $_smarty_tpl->tpl_vars['client']->value) {
$_smarty_tpl->tpl_vars['client']->_loop = true;
?>
          <option<?php if (($_smarty_tpl->tpl_vars['scope']->value['cal_params']['cal_search']['client_id']==$_smarty_tpl->tpl_vars['client']->value['id'])) {?> selected="selected"<?php }?> value="<?php echo $_smarty_tpl->tpl_vars['client']->value['id'];?>
"><?php echo return_if_empty($_smarty_tpl->tpl_vars['client']->value['name'],$_smarty_tpl->tpl_vars['client']->value['id']);?>
</option>
        <?php } ?>                                            
      </select>
      <span class="input-icon"><i class="fa fa-building-o"></i></span>
    </div>               
    <?php } else { ?>
    <input type="text" name="client_id" placeholder="client" class="" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_params']['client_id'];?>
">
    <?php }?>

    <?php if ((0)) {?>
    <input type="text" name="host_id"   placeholder="host" class="" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['cal_params']['host_id'];?>
">
    <?php } else { ?>
    <div class="col-md-2 relative nogutter">
      <select class="form-control" id="host_id" name="host_id">
        <option <?php if ((!$_smarty_tpl->tpl_vars['scope']->value['cal_params']['cal_search']['host_id'])) {?> selected="selected"<?php }?> value="0">All Hosts</option>
        <?php  $_smarty_tpl->tpl_vars['host'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['host']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['cal_params']['hosts']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['host']->key => $_smarty_tpl->tpl_vars['host']->value) {
$_smarty_tpl->tpl_vars['host']->_loop = true;
?>
          <option<?php if (($_smarty_tpl->tpl_vars['scope']->value['cal_params']['cal_search']['host_id']==$_smarty_tpl->tpl_vars['host']->value['id'])) {?> selected="selected"<?php }?> value="<?php echo $_smarty_tpl->tpl_vars['host']->value['id'];?>
"><?php echo return_if_empty($_smarty_tpl->tpl_vars['host']->value['name'],$_smarty_tpl->tpl_vars['host']->value['id']);?>
</option>
        <?php } ?>                                            
      </select>
      <span class="input-icon"><i class="icon-user"></i></span>
    </div>               
    <?php }?>
    
    <div class="col-md-2 relative nogutter">
      <select class="form-control" id="max_guests" name="max_guests">
        <option <?php if ((!$_smarty_tpl->tpl_vars['scope']->value['cal_params']['cal_search']['max_guests'])) {?> selected="selected"<?php }?> value="0">Guests</option>
        <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['name'] = 'max_guests';
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['loop'] = is_array($_loop=8) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['step'] = ((int) 1) == 0 ? 1 : (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['show'] = true;
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['max'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['loop'];
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['start'] < 0)
    $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['start'] = max($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['step'] > 0 ? 0 : -1, $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['loop'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['start']);
else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['start'] = min($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['loop'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['loop']-1);
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['show']) {
    $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['total'] = min(ceil(($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['loop'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['start'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['start']+1)/abs($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['step'])), $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['max']);
    if ($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['total'] == 0)
        $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['show'] = false;
} else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['total'] = 0;
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['show']):

            for ($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['index'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['iteration'] = 1;
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['iteration'] <= $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['total'];
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['index'] += $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['step'], $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['iteration']++):
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['rownum'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['iteration'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['index_prev'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['index'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['index_next'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['index'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['first']      = ($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['iteration'] == 1);
$_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['last']       = ($_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['iteration'] == $_smarty_tpl->tpl_vars['smarty']->value['section']['max_guests']['total']);
?>
          <option<?php if (($_smarty_tpl->tpl_vars['scope']->value['cal_params']['cal_search']['max_guests']==$_smarty_tpl->getVariable('smarty')->value['section']['max_guests']['index'])) {?> selected="selected"<?php }?> value="<?php echo $_smarty_tpl->getVariable('smarty')->value['section']['max_guests']['index'];?>
"><?php echo $_smarty_tpl->getVariable('smarty')->value['section']['max_guests']['index'];?>
 Guest<?php if (($_smarty_tpl->getVariable('smarty')->value['section']['max_guests']['index']!=1)) {?>s<?php }?> </option>
        <?php endfor; endif; ?>                                            
        <option <?php if (($_smarty_tpl->tpl_vars['scope']->value['cal_params']['cal_search']['max_guests']>=8)) {?> selected="selected"<?php }?> value="8">8+ Guests</option>
      </select>
      <span class="input-icon"><i class="icon-users"></i></span>
    </div>               

    <input type="submit" class="btn btn-primary" value="Search">              
    <!--input type="submit" class="btn btn-danger form-resubmit" value="Reset">              
    <input type="submit" class="btn btn-danger reset-form-submit" value="R"-->              

  </form>

<?php }} ?>
