<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:05:24
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-edit-amenities.html" */ ?>
<?php /*%%SmartyHeaderCode:1396575908551c0934690de2-45233051%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '667c682d33ec1d4fc6f34e02d6786784d30e385f' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-edit-amenities.html',
      1 => 1427900724,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1396575908551c0934690de2-45233051',
  'function' => 
  array (
  ),
  'variables' => 
  array (
    'scope' => 0,
    'k' => 0,
    'facs' => 0,
    'fac' => 0,
  ),
  'has_nocache_code' => false,
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c0934757ad9_37315456',
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c0934757ad9_37315456')) {function content_551c0934757ad9_37315456($_smarty_tpl) {?><?php if (!is_callable('smarty_modifier_capitalize')) include '/usr/share/php/Smarty/plugins/modifier.capitalize.php';
?>
                        <form id="facilities_form" class="checkbox_group ajax-submit autosave-oof" data-obj_type="<?php echo $_smarty_tpl->tpl_vars['scope']->value['type'];?>
" data-obj_id="<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
"  data-handler="save">
                          <input name="obj_type" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['type'];?>
">
                          <input name="id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
">
                          <input name="facilities" type="hidden" id="facilities" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['facilities'];?>
" class="cb_target form-control">
                          <?php  $_smarty_tpl->tpl_vars['facs'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['facs']->_loop = false;
 $_smarty_tpl->tpl_vars['k'] = new Smarty_Variable;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['amenities']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['facs']->key => $_smarty_tpl->tpl_vars['facs']->value) {
$_smarty_tpl->tpl_vars['facs']->_loop = true;
 $_smarty_tpl->tpl_vars['k']->value = $_smarty_tpl->tpl_vars['facs']->key;
?>
                          <div class="row table">
                              <div class="col-md-5 table-cell">
                                  <h4><?php echo smarty_modifier_capitalize($_smarty_tpl->tpl_vars['k']->value);?>
</h4>
                              </div>              
                              <div class="col-md-7 table-cell">
                              <?php  $_smarty_tpl->tpl_vars['fac'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['fac']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['facs']->value; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['fac']->key => $_smarty_tpl->tpl_vars['fac']->value) {
$_smarty_tpl->tpl_vars['fac']->_loop = true;
?>
                                  <div class="checkbox">                                
                                       <label><input name="fac_<?php echo $_smarty_tpl->tpl_vars['fac']->value['id'];?>
" data-id="<?php echo $_smarty_tpl->tpl_vars['fac']->value['id'];?>
" data-target="#facilities" value="<?php echo $_smarty_tpl->tpl_vars['fac']->value['id'];?>
" type="checkbox" 
                                       <?php if (($_smarty_tpl->tpl_vars['fac']->value['value']==1)) {?>checked<?php }?>
                                       /><?php echo smarty_modifier_capitalize($_smarty_tpl->tpl_vars['fac']->value['name']);?>
</label>
                                  </div>
                              <?php } ?> 
                              </div>
                          </div>
                          <?php } ?>
                            <hr>
                            <input type="submit" class="btn btn-primary" value="Save Changes">
                          
                        </form>
                                                                                                                               

<?php }} ?>
