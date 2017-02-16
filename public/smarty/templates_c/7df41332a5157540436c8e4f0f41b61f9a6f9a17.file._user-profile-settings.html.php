<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:06:01
         compiled from "/web/comps/php/apt-dev/smarty/templates/_user-profile-settings.html" */ ?>
<?php /*%%SmartyHeaderCode:671280096551c174cb32732-41259195%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '7df41332a5157540436c8e4f0f41b61f9a6f9a17' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_user-profile-settings.html',
      1 => 1427904361,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '671280096551c174cb32732-41259195',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c174cc030d7_43732758',
  'variables' => 
  array (
    'user' => 0,
    'site' => 0,
    'scope' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c174cc030d7_43732758')) {function content_551c174cc030d7_43732758($_smarty_tpl) {?>
                    <div class="row">
                        <div class="col-md-5">
                            <form id="user_profile_form" class="ajax-submit" data-handler="save">
                                <input type="hidden" name="obj_type"value="user_profile" />
                                <input type="hidden" name="id"  value="<?php echo $_smarty_tpl->tpl_vars['user']->value['profile_id'];?>
" />
                                <input type="hidden" name="user_id" value="<?php echo $_smarty_tpl->tpl_vars['user']->value['id'];?>
" />
                                <input type="hidden" name="site_id" value="<?php echo $_smarty_tpl->tpl_vars['site']->value['id'];?>
" />
                            
                                <h4>Personal Infomation</h4>
                                <div class="form-group form-group-icon-left"><i class="fa fa-user input-icon"></i>
                                    <label>First Name</label>
                                    <input name="first_name" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['first_name'];?>
" type="text" />
                                </div>                 
                                <div class="form-group form-group-icon-left"><i class="fa fa-user input-icon"></i>
                                    <label>Last Name</label>
                                    <input name="last_name" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['last_name'];?>
" type="text" />
                                </div>
                                <div class="form-group form-group-icon-left"><i class="fa fa-user input-icon"></i>
                                    <label>Display Name</label>
                                    <input name="display_name" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['display_name'];?>
" type="text" />
                                </div>
                                <div class="form-group form-group-icon-left"><i class="fa fa-envelope input-icon"></i>
                                    <label>E-mail</label>
                                    <input name="email_address" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['email_address'];?>
" type="text" />
                                </div>
                                <div class="form-group form-group-icon-left"><i class="fa fa-phone input-icon"></i>
                                    <label>Phone Number</label>
                                    <input name="mobile" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['phone1'];?>
" type="text" />
                                </div>
                                <div class="gap gap-small"></div>
                                <h4>Location</h4>
                                                              
                                <div class="form-group">
                                    <label>Timezone</label>
                                    <select name="timezone" id="timezone" data-value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['timezone'];?>
" 
                                       class="form-control auto-select" autofocus="autofocus" autocorrect="off" autocomplete="off">
                                      <option value="" selected>Select a timezone...</option>
                                      <?php echo $_smarty_tpl->getSubTemplate ("_timezones.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                                    </select>
                                </div>
                                
                                <!--div class="form-group form-group-icon-left"><i class="fa fa-plane input-icon"></i>
                                    <label>Home Airport</label>
                                    <input class="form-control" value="London Heathrow Airport (LHR)" type="text" />
                                </div-->
                                <div class="form-group">
                                    <label>Street Address</label>
                                    <input name="address1" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['address1'];?>
" type="text" />
                                </div>
                                <div class="form-group">
                                    <label>City</label>
                                    <input name="city" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['city'];?>
" type="text" />
                                </div>
                                <div class="form-group">
                                    <label>State/Province/Region</label>
                                    <input name="state" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['state'];?>
" type="text" />
                                </div>
                                <div class="form-group">
                                    <label>ZIP code/Postal code</label>
                                    <input name="zip" class="form-control" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['zip'];?>
" type="text" />
                                </div>
                                <div class="form-group">
                                    <label>Country</label>
                                    <select name="country" id="country" data-value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['country'];?>
" class="form-control auto-select" autofocus="autofocus" autocorrect="off" autocomplete="off">
                                      <option value=""></option>
                                      <?php echo $_smarty_tpl->getSubTemplate ("_countries.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                                    </select>
                                </div>
                                <hr>
                                <input type="submit" class="btn btn-primary" value="Save Changes">
                            </form>
                        </div>
                        <div class="col-md-4 col-md-offset-1">
                            <h4>Change Password</h4>
                            <form>
                                <div class="form-group form-group-icon-left"><i class="fa fa-lock input-icon"></i>
                                    <label>Current Password</label>
                                    <input class="form-control" type="password" />
                                </div>
                                <div class="form-group form-group-icon-left"><i class="fa fa-lock input-icon"></i>
                                    <label>New Password</label>
                                    <input class="form-control" type="password" />
                                </div>
                                <div class="form-group form-group-icon-left"><i class="fa fa-lock input-icon"></i>
                                    <label>New Password Again</label>
                                    <input class="form-control" type="password" />
                                </div>
                                <hr />
                                <input class="btn btn-primary" type="submit" value="Change Password" />
                            </form>
                            <div class="gap gap-small"></div>
                            <h4>Photo</h4>
                            <?php echo $_smarty_tpl->tpl_vars['scope']->value['uploader'];?>


                        </div>
                        
                    </div>


<?php }} ?>
