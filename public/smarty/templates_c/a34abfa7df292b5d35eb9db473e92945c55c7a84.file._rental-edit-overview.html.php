<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:11:40
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-edit-overview.html" */ ?>
<?php /*%%SmartyHeaderCode:397985256551c092654a370-63542868%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'a34abfa7df292b5d35eb9db473e92945c55c7a84' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-edit-overview.html',
      1 => 1427901100,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '397985256551c092654a370-63542868',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c09265f2952_66539713',
  'variables' => 
  array (
    'scope' => 0,
    'user' => 0,
    'site' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c09265f2952_66539713')) {function content_551c09265f2952_66539713($_smarty_tpl) {?>
                    
                    <!--h4>Statistics</h4>
                    <ul class="list list-inline user-profile-statictics mb30">
                        <li><i class="fa fa-dashboard user-profile-statictics-icon"></i>
                            <h5>20</h5>
                            <p>Nights</p>
                        </li>
                        <li><i class="fa fa-globe user-profile-statictics-icon"></i>
                            <h5>2</h5>
                            <p>Guests</p>
                        </li>
                        <li><i class="fa fa-building-o user-profile-statictics-icon"></i>
                            <h5><?php echo currency2html($_smarty_tpl->tpl_vars['scope']->value['currency']);?>
1500</h5>
                            <p>Earned</p>
                        </li>
                    </ul-->
                    
                    
                    <div class="clearfix">
                      <h4 class="pull-left inline">Name</h4>
                      <div class="checkbox pull-right">
                        <label>
                          <input type="checkbox" data-target="#property_active" class="bootstrap-toggle cb-update-target" <?php if (($_smarty_tpl->tpl_vars['scope']->value['active'])) {?>checked<?php }?> data-toggle="toggle" data-onstyle="success" data-offstyle="danger">                            
                        </label>                               
                      </div>
                    </div>
                    <form id="basic-edit-form" class="ajax-submit autosave" data-obj_type="<?php echo $_smarty_tpl->tpl_vars['scope']->value['type'];?>
" data-obj_id="<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
" data-handler="save">
                      <input name="user_id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['user']->value['id'];?>
" />
                      <input name="site_id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['site']->value['id'];?>
" />
                      <input name="obj_type" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['type'];?>
" />
                      <input name="id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
" />
                      <input type="hidden" name="active" id="property_active" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['active'];?>
">                            


                      <div class="form-group">
                          <label>Name</label>
                          <input name="name" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['name'];?>
" type="text" />
                      </div>
                      <hr>
                      <h4>Location</h4>
                      <!--div class="form-group form-group-icon-left"><i class="fa fa-plane input-icon"></i>
                          <label>Home Airport</label>
                          <input name="aiport" class="form-control" value="London Heathrow Airport (LHR)" type="text" />
                      </div-->
                      <div class="form-group">
                          <label>Street Address and number</label>
                          <input name="address_street" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['address_street'];?>
" type="text" />
                          <input name="address_number" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['address_number'];?>
" type="text" />
                      </div>
                      <div class="form-group">
                          <label>City</label>
                          <input name="address_city" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['address_city'];?>
" type="text" />
                      </div>
                      <div class="form-group">
                          <label>State/Province/Region</label>
                          <input name="address_state" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['address_state'];?>
" type="text" />
                      </div>
                      <div class="form-group">
                          <label>ZIP code/Postal code</label>
                          <input name="address_postcode" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['address_postcode'];?>
" type="text" />
                      </div>
                      <div class="form-group">
                          <label>Country</label>
                          <input name="address_country" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['address_country'];?>
" type="text" />
                      </div>
                      <hr>

                      <input type="submit" class="btn btn-primary" value="Save Changes">                      
                    </form>
                    
                    <div id="map-canvas" style="width:100%; height:400px;"></div>
                 

<?php }} ?>
