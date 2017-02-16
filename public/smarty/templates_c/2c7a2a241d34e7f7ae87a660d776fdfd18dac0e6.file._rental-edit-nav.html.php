<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:08:12
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-edit-nav.html" */ ?>
<?php /*%%SmartyHeaderCode:767582138551bac7fe49436-63436433%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '2c7a2a241d34e7f7ae87a660d776fdfd18dac0e6' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-edit-nav.html',
      1 => 1427900892,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '767582138551bac7fe49436-63436433',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551bac7fe9e481_45193608',
  'variables' => 
  array (
    'scope' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551bac7fe9e481_45193608')) {function content_551bac7fe9e481_45193608($_smarty_tpl) {?>
                        <ul class="list user-profile-nav">
                            <li><a href="/edit-property/<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
?view=_rental-edit-overview.html" class="smtlink" data-tpl="_rental-edit-overview.html"><i class="fa fa-user"></i>Overview</a></li>
                            <li><a href="/edit-property/<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
?view=_rental-edit-pricing.html" class="smtlink" data-tpl="_rental-edit-pricing.html"><i class="fa fa-credit-card"></i>Pricing</a></li>
                            <li><a href="/edit-property/<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
?view=_rental-edit-settings.html" class="smtlink" data-tpl="_rental-edit-settings.html"><i class="fa fa-cog"></i>Settings</a></li>
                            <li><a href="/edit-property/<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
?view=_rental-edit-photos.html" class="smtlink" data-tpl="_rental-edit-photos.html"><i class="fa fa-camera"></i>Photos</a></li>
                            <li><a href="/edit-property/<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
?view=_rental-edit-description.html" class="smtlink" data-tpl="_rental-edit-description.html"><i class="fa fa-file-text"></i>Description</a></li>
                            <li><a href="/edit-property/<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
?view=_rental-edit-amenities.html" class="smtlink" data-tpl="_rental-edit-amenities.html"><i class="fa fa-check"></i>Amenities</a></li>
                            <li><a href="/edit-property/<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
?view=_rental-edit-calendar.html" class="smtlink" data-tpl="_rental-edit-calendar.html"><i class="fa fa-calendar"></i>Calendar</a></li>
                        </ul>
                                                                                      

<?php }} ?>
