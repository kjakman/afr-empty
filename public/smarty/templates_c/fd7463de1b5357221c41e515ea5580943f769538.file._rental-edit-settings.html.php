<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:05:37
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-edit-settings.html" */ ?>
<?php /*%%SmartyHeaderCode:928087932551c092ba6eca4-86179907%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'fd7463de1b5357221c41e515ea5580943f769538' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-edit-settings.html',
      1 => 1427900737,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '928087932551c092ba6eca4-86179907',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c092bdc2b00_14862494',
  'variables' => 
  array (
    'scope' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c092bdc2b00_14862494')) {function content_551c092bdc2b00_14862494($_smarty_tpl) {?>
                        <form id="property_settings_form" class="ajax-submit autosave" data-handler="save">
                          <input type="hidden" name="obj_type" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['type'];?>
">
                          <input type="hidden" name="id" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
">
                          <input type="hidden" name="book_direct" id="book_direct" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['book_direct'];?>
">                            
                          <h4>Settings</h4>
                          <div class="checkbox form-group">
                            <label>                            
                              <input type="checkbox" data-target="#book_direct" class="bootstrap-toggle cb-update-target" <?php if (($_smarty_tpl->tpl_vars['scope']->value['book_direct'])) {?>checked<?php }?> data-toggle="toggle" data-onstyle="success" data-offstyle="danger">
                              Allow Direct Booking?
                            </label>                               
                          </div>
                          <div class="form-group form-group-icon-left form-group-select-plus">
                              <label>Sleeps </label>
                              <div class="btn-group btn-group-select-num<?php if (($_smarty_tpl->tpl_vars['scope']->value['max_guests']>=8)) {?> hidden<?php }?>" data-toggle="buttons">
                                  <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['name'] = 'ng';
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] = is_array($_loop=8) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] = ((int) 1) == 0 ? 1 : (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = true;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'];
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] < 0)
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = max($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? 0 : -1, $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']);
else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = min($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop']-1);
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']) {
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = min(ceil(($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']+1)/abs($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'])), $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max']);
    if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] == 0)
        $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = false;
} else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = 0;
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']):

            for ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] = 1;
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] <= $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'];
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] += $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration']++):
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['rownum'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_prev'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_next'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['first']      = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == 1);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['last']       = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total']);
?>
                                    <label class="btn btn-primary<?php if (($_smarty_tpl->tpl_vars['scope']->value['max_guests']==$_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'])) {?> active<?php }?>">
                                      <input type="radio" name="options" class="set-target-value" data-target="#max_guests" data-value="<?php echo $_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'];?>
"/>
                                      <?php echo $_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'];?>

                                    </label>
                                  <?php endfor; endif; ?>                                            
                                  <label class="btn btn-primary"><input type="radio" name="options" />8+</label>
                              </div>
                              <select name="max_guests" id="max_guests" class="form-control<?php if (($_smarty_tpl->tpl_vars['scope']->value['max_guests']<8)) {?> hidden<?php }?>">
                                  <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['name'] = 'ng';
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] = is_array($_loop=15) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] = ((int) 1) == 0 ? 1 : (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = true;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'];
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] < 0)
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = max($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? 0 : -1, $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']);
else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = min($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop']-1);
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']) {
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = min(ceil(($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']+1)/abs($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'])), $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max']);
    if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] == 0)
        $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = false;
} else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = 0;
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']):

            for ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] = 1;
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] <= $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'];
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] += $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration']++):
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['rownum'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_prev'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_next'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['first']      = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == 1);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['last']       = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total']);
?>
                                    <option<?php if (($_smarty_tpl->tpl_vars['scope']->value['max_guests']==$_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'])) {?> selected="selected"<?php }?>><?php echo $_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'];?>
</option>
                                  <?php endfor; endif; ?>                                            
                              </select>
                          </div>
                          <div class="form-group form-group-icon-left form-group-select-plus">
                              <label>Bedrooms </label>
                              <div class="btn-group btn-group-select-num<?php if (($_smarty_tpl->tpl_vars['scope']->value['num_bedrooms']>='f')) {?> hidden<?php }?>" data-toggle="buttons">
                                  <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['nb'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['name'] = 'nb';
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['loop'] = is_array($_loop=4) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['step'] = ((int) 1) == 0 ? 1 : (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['show'] = true;
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['max'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['loop'];
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['start'] < 0)
    $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['start'] = max($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['step'] > 0 ? 0 : -1, $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['loop'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['start']);
else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['start'] = min($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['loop'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['loop']-1);
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['show']) {
    $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['total'] = min(ceil(($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['loop'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['start'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['start']+1)/abs($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['step'])), $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['max']);
    if ($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['total'] == 0)
        $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['show'] = false;
} else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['total'] = 0;
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['show']):

            for ($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['index'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['iteration'] = 1;
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['iteration'] <= $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['total'];
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['index'] += $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['step'], $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['iteration']++):
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['rownum'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['iteration'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['index_prev'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['index'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['index_next'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['index'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['first']      = ($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['iteration'] == 1);
$_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['last']       = ($_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['iteration'] == $_smarty_tpl->tpl_vars['smarty']->value['section']['nb']['total']);
?>
                                    <label class="btn btn-primary<?php if (($_smarty_tpl->tpl_vars['scope']->value['num_bedrooms']==$_smarty_tpl->getVariable('smarty')->value['section']['nb']['index'])) {?> active<?php }?>">
                                      <input type="radio" name="options" class="set-target-value" data-target="#num_bedrooms" data-value="<?php echo $_smarty_tpl->getVariable('smarty')->value['section']['nb']['index'];?>
"/>
                                      <?php echo $_smarty_tpl->getVariable('smarty')->value['section']['nb']['index'];?>

                                    </label>
                                  <?php endfor; endif; ?>                                            
                                  <label class="btn btn-primary"><input type="radio" name="options" />4+</label>
                              </div>
                              <select name="num_bedrooms" id="num_bedrooms" class="form-control<?php if (($_smarty_tpl->tpl_vars['scope']->value['num_bedrooms']<4)) {?> hidden<?php }?>">
                                  <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['name'] = 'ng';
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] = is_array($_loop=15) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] = ((int) 1) == 0 ? 1 : (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = true;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'];
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] < 0)
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = max($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? 0 : -1, $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']);
else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = min($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop']-1);
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']) {
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = min(ceil(($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']+1)/abs($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'])), $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max']);
    if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] == 0)
        $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = false;
} else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = 0;
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']):

            for ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] = 1;
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] <= $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'];
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] += $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration']++):
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['rownum'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_prev'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_next'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['first']      = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == 1);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['last']       = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total']);
?>
                                    <option<?php if (($_smarty_tpl->tpl_vars['scope']->value['num_bedrooms']==$_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'])) {?> selected="selected"<?php }?>><?php echo $_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'];?>
</option>
                                  <?php endfor; endif; ?>                                            
                              </select>
                          </div>
                          <div class="form-group form-group-icon-left form-group-select-plus">
                              <label>Bathrooms </label>
                              <div class="btn-group btn-group-select-num<?php if (($_smarty_tpl->tpl_vars['scope']->value['num_bathrooms']>=4)) {?> hidden<?php }?>" data-toggle="buttons">
                                  <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['name'] = 'nbr';
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['loop'] = is_array($_loop=4) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['step'] = ((int) 1) == 0 ? 1 : (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['show'] = true;
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['max'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['loop'];
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['start'] < 0)
    $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['start'] = max($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['step'] > 0 ? 0 : -1, $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['loop'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['start']);
else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['start'] = min($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['loop'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['loop']-1);
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['show']) {
    $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['total'] = min(ceil(($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['loop'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['start'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['start']+1)/abs($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['step'])), $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['max']);
    if ($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['total'] == 0)
        $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['show'] = false;
} else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['total'] = 0;
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['show']):

            for ($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['index'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['iteration'] = 1;
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['iteration'] <= $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['total'];
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['index'] += $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['step'], $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['iteration']++):
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['rownum'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['iteration'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['index_prev'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['index'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['index_next'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['index'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['first']      = ($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['iteration'] == 1);
$_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['last']       = ($_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['iteration'] == $_smarty_tpl->tpl_vars['smarty']->value['section']['nbr']['total']);
?>
                                    <label class="btn btn-primary<?php if (($_smarty_tpl->tpl_vars['scope']->value['num_bathrooms']==$_smarty_tpl->getVariable('smarty')->value['section']['nbr']['index'])) {?> active<?php }?>">
                                      <input type="radio" name="options" name="options" class="set-target-value" data-target="#num_bathrooms" data-value="<?php echo $_smarty_tpl->getVariable('smarty')->value['section']['nbr']['index'];?>
"/>
                                      <?php echo $_smarty_tpl->getVariable('smarty')->value['section']['nbr']['index'];?>

                                    </label>
                                  <?php endfor; endif; ?>                                            
                                  <label class="btn btn-primary"><input type="radio" name="options" />4+</label>
                              </div>
                              <select name="num_bathrooms" id="num_bathrooms" class="form-control<?php if (($_smarty_tpl->tpl_vars['scope']->value['num_bathrooms']<4)) {?> hidden<?php }?>">
                                  <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['name'] = 'ng';
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] = is_array($_loop=15) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] = ((int) 1) == 0 ? 1 : (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = true;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'];
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] < 0)
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = max($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? 0 : -1, $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']);
else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = min($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop']-1);
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']) {
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = min(ceil(($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']+1)/abs($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'])), $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max']);
    if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] == 0)
        $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = false;
} else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = 0;
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']):

            for ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] = 1;
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] <= $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'];
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] += $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration']++):
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['rownum'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_prev'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_next'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['first']      = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == 1);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['last']       = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total']);
?>
                                    <option<?php if (($_smarty_tpl->tpl_vars['scope']->value['num_bathrooms']==$_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'])) {?> selected="selected"<?php }?>><?php echo $_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'];?>
</option>
                                  <?php endfor; endif; ?>                                            
                              </select>
                          </div>

                            <hr>
                            <input type="submit" class="btn btn-primary" value="Save Changes">
                        </form>


<?php }} ?>
