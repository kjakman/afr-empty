<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:04:11
         compiled from "/web/comps/php/apt-dev/smarty/templates/inbox.html" */ ?>
<?php /*%%SmartyHeaderCode:284677526551c169d1faf39-20551407%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '227d25414b656669888598e6315ecdf2ef5eb67b' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/inbox.html',
      1 => 1427904251,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '284677526551c169d1faf39-20551407',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c169d2ed727_51298622',
  'variables' => 
  array (
    'scope' => 0,
    'reservation' => 0,
    'rental' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c169d2ed727_51298622')) {function content_551c169d2ed727_51298622($_smarty_tpl) {?>
        <div class="container">
          <?php if (($_smarty_tpl->tpl_vars['scope']->value['thread_id'])) {?>
            <?php $_smarty_tpl->tpl_vars['reservation'] = new Smarty_variable($_smarty_tpl->tpl_vars['scope']->value['reservation'], null, 0);?>
            <?php $_smarty_tpl->tpl_vars['rental'] = new Smarty_variable($_smarty_tpl->tpl_vars['scope']->value['rental'], null, 0);?>

          <h3>Conversation with <?php echo $_smarty_tpl->tpl_vars['scope']->value['other_user']['display_name'];?>
</h3>
          <div class="row">
            <div class="col-md-8">
              <?php echo $_smarty_tpl->getSubTemplate ("_inbox-thread.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>
                    
            </div>
            <div class="col-md-4">
              <div class="panel panel-default">
                <div class="panel-body nopadding">
                <?php echo $_smarty_tpl->getSubTemplate ("_user-profile-panel.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array('user'=>$_smarty_tpl->tpl_vars['scope']->value['other_user']), 0);?>
                   
                </div>
              </div>            
              <div class="panel panel-default">
                <div class="panel-body nopadding">
                <?php if (($_smarty_tpl->tpl_vars['reservation']->value)) {?>
                <?php echo $_smarty_tpl->getSubTemplate ("_booking-panel.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                <?php } elseif (($_smarty_tpl->tpl_vars['rental']->value)) {?>
                <?php echo $_smarty_tpl->getSubTemplate ("_rental-panel.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                <?php }?>
                </div>
              </div>            
            </div>
          </div>
          <?php } else { ?>
          <h3>Inbox</h3>
          <?php echo $_smarty_tpl->getSubTemplate ("_inbox-threads.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

          <?php }?>
        </div>

<?php }} ?>
