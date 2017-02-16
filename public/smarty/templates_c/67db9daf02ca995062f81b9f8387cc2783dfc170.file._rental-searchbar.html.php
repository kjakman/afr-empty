<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:59:03
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-searchbar.html" */ ?>
<?php /*%%SmartyHeaderCode:683854500551b9a58b2e146-91603880%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '67db9daf02ca995062f81b9f8387cc2783dfc170' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-searchbar.html',
      1 => 1427903943,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '683854500551b9a58b2e146-91603880',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551b9a58d09073_46661916',
  'variables' => 
  array (
    'site' => 0,
    'scope' => 0,
    'global' => 0,
    'autocomplete' => 0,
    'date_size' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551b9a58d09073_46661916')) {function content_551b9a58d09073_46661916($_smarty_tpl) {?>
    <input type="hidden" placeholder="site" name="site_id" value="<?php echo $_smarty_tpl->tpl_vars['site']->value['id'];?>
">
    <input type="hidden" placeholder="type" name="t" value="<?php echo return_if_empty($_smarty_tpl->tpl_vars['scope']->value['property_type'],'shortstay');?>
">
    <input type="hidden" placeholder="center" name="center" id="center" class='location-center' value='<?php echo return_if_empty($_GET['center'],$_smarty_tpl->tpl_vars['scope']->value['center']);?>
'>
    <input type="hidden" placeholder="bounds" name="bounds" id="bounds" class='location-bounds' size="40" data-target="location_id" data-target_display="loc"  value='<?php echo return_if_empty($_GET['bounds'],$_smarty_tpl->tpl_vars['scope']->value['bounds']);?>
'>
    <input type="hidden" placeholder="loc_types" name="loc_types" value="<?php echo return_if_empty($_smarty_tpl->tpl_vars['global']->value['location_types'],'landmark,airport');?>
">
    <input type="hidden" placeholder="city_id" name="city_id" value="<?php echo $_SESSION['city_id'];?>
">
    <?php if (($_smarty_tpl->tpl_vars['autocomplete']->value)) {?>
    <?php $_smarty_tpl->tpl_vars['date_size'] = new Smarty_variable(2, null, 0);?>
    <div class="col-md-4 relative nogutter">
      <?php echo $_smarty_tpl->getSubTemplate ("_rental-search-location.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

      <!--div class="form-group form-group-filled">
        <input name="loc" type="text" id="loc" placeholder="Where are you going?" class="jq-autocomplete form-control ui-autocomplete-input" autocomplete="off" 
          value="<?php echo $_GET['loc'];?>
"
          data-target="location_id" 
          data-options='<?php echo json_encode($_smarty_tpl->tpl_vars['scope']->value['autocomplete_options']);?>
'
          data-search_options='<?php echo json_encode($_smarty_tpl->tpl_vars['scope']->value['autocomplete_search_options']);?>
'>
      </div>
      <span class="input-icon"><i class="glyphicon glyphicon-map-marker"></i></span-->
    </div>
    <?php } else { ?>
    <?php $_smarty_tpl->tpl_vars['date_size'] = new Smarty_variable(3, null, 0);?>
      <!--input type="hidden" value="<?php echo $_GET['bounds'];?>
"        name="location_bounds"-->    
    <input type="hidden" value="<?php echo $_GET['loc'];?>
" name="loc">    
    <?php }?>
    
    <div class="col-md-<?php echo $_smarty_tpl->tpl_vars['date_size']->value;?>
 relative nogutter">
      <input type="text" value="<?php echo $_GET['in_disp'];?>
" class="form-control datepicker" id="in_disp" name="in_disp" placeholder="Checkin" data-dependent_field="out">
      <input type="hidden" value="<?php echo $_GET['in'];?>
" id="in" name="in">          
      <span class="input-icon"><i class="icon-calendar"></i></span>
    </div>
    <div class="col-md-<?php echo $_smarty_tpl->tpl_vars['date_size']->value;?>
 relative nogutter">
      <input type="text" value="<?php echo $_GET['out_disp'];?>
" class="form-control datepicker datepicker-2" id="out_disp" name="out_disp" placeholder="Checkout">    
      <input type="hidden" value="<?php echo $_GET['out'];?>
" id="out" name="out">    
      <span class="input-icon"><i class="icon-calendar"></i></span>
    </div>

    <div class="col-md-2 relative nogutter">
      <select class="form-control" id="ng" name="ng">
        <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['name'] = 'ng';
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] = is_array($_loop=16) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
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
          <option<?php if (($_GET['ng']==$_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'])) {?> selected="selected"<?php }?> value="<?php echo $_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'];?>
"><?php echo $_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'];?>
 Guest<?php if (($_smarty_tpl->getVariable('smarty')->value['section']['ng']['index']!=1)) {?>s<?php }?> </option>
        <?php endfor; endif; ?>                                            
        <option <?php if (($_GET['ng']>15)) {?> selected="selected"<?php }?> value="16">16+ Guests</option>
      </select>
      <span class="input-icon"><i class="icon-users"></i></span>
    </div>
    <div class="col-md-2 relative nogutter">
      <button type="submit" class="btn btn-success close-collapse" id="submit-check" data-target="#search-more"> Search </button>
    </div>
  
<!--
http://test.hitabrick.com/serviced-apartment/?search=1&
t=shortstay&
location_id_textbox=Portugal&
location_lat=39.39987199999999&
location_long=-8.224454000000037&
bounds=%5B%5B36.9601772%2C-9.51711069999999%5D%2C%5B42.1542048%2C-6.190209099999947%5D%5D&
in_disp=8-3-2015&
in=2015-03-08&
out_disp=15-3-2015&
out=2015-03-15&
ng=2
-->


<?php }} ?>
