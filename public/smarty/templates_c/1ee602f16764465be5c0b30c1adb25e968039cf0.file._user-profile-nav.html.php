<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:20:46
         compiled from "/web/comps/php/apt-dev/smarty/templates/_user-profile-nav.html" */ ?>
<?php /*%%SmartyHeaderCode:587148962551c171478f594-96993178%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '1ee602f16764465be5c0b30c1adb25e968039cf0' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_user-profile-nav.html',
      1 => 1427905246,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '587148962551c171478f594-96993178',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c17147b14e2_86829424',
  'variables' => 
  array (
    'scope' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c17147b14e2_86829424')) {function content_551c17147b14e2_86829424($_smarty_tpl) {?>
                        <ul class="list user-profile-nav">
                          <?php if (($_smarty_tpl->tpl_vars['scope']->value['auth_edit'])) {?>
                          <li><a href="/profile/?view=_user-profile-overview.html" class="smtlink" data-tpl="_user-profile-overview.html"><i class="fa fa-user"></i>Overview</a>
                          </li>
                          <li><a href="/profile/?view=_user-profile-settings.html" class="smtlink" data-tpl="_user-profile-settings.html"><i class="fa fa-cog"></i>Settings</a>
                          </li>
                          <li><a href="/profile/?view=_user-profile-history.html" class="smtlink" data-tpl="_user-profile-history.html"><i class="fa fa-clock-o"></i>Booking History</a>
                          </li>
                          <li><a href="/profile/?view=_user-profile-cards.html" class="smtlink" data-tpl="_user-profile-cards.html"><i class="fa fa-credit-card"></i>Credit/Debit Cards</a>
                          </li>
                          <li><a href="/profile/?view=_user-profile-wishlist.html" class="smtlink" data-tpl="_user-profile-wishlist.html"><i class="fa fa-heart-o"></i>Wishlist</a>
                          </li>                       
                          <li><a href="/profile/?view=_user-profile-inbox.html" class="smtlink" data-tpl="_user-profile-inbox.html"><i class="fa fa-envelope-o"></i>Inbox</a>
                          </li>                       
                          <!--li><a href="/profile/?view=_user-profile-photos.html" class="smtlink" data-tpl="_user-profile-photos.html"><i class="fa fa-camera"></i>My Travel Photos</a>
                          </li-->
                          <?php } else { ?>
                          <li><a href="/profile/?view=_user-profile-inbox.html" class="smtlink" data-tpl="_user-profile-message.html"><i class="fa fa-envelope-o"></i>Send a message</a>
                          </li>
                          <?php }?>
                        </ul>


<?php }} ?>
