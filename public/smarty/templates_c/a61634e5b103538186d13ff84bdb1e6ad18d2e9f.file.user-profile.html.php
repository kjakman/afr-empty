<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:20:46
         compiled from "/web/comps/php/apt-dev/smarty/templates/user-profile.html" */ ?>
<?php /*%%SmartyHeaderCode:866104785551c17146d33f4-18861765%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'a61634e5b103538186d13ff84bdb1e6ad18d2e9f' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/user-profile.html',
      1 => 1427905246,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '866104785551c17146d33f4-18861765',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c1714785e84_75327845',
  'variables' => 
  array (
    'scope' => 0,
    'tpl' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c1714785e84_75327845')) {function content_551c1714785e84_75327845($_smarty_tpl) {?>

        <div class="container">
            <h1 class="page-title">Travel Profile</h1>
        </div>

        <div class="container">
            <div class="row">
                <div class="col-md-3">
                    <aside class="user-profile-sidebar">
                        <div class="user-profile-avatar text-center">
                            <img src="<?php echo $_smarty_tpl->tpl_vars['scope']->value['profile_picture'];?>
" alt="<?php echo $_smarty_tpl->tpl_vars['scope']->value['full_name'];?>
" title="AMaze" />
                            <h5><?php echo $_smarty_tpl->tpl_vars['scope']->value['display_name'];?>
</h5>
                            <p>Member Since <?php echo sql2human($_smarty_tpl->tpl_vars['scope']->value['created']);?>
</p>
                        </div>
                        <nav data-target="#user-profile-container">
                        <nav data-target="#user-profile-container" 
                             data-controller="traveler_profile" 
                             data-data='<?php echo json_encode($_smarty_tpl->tpl_vars['scope']->value['data']);?>
'
                             data-success_handler="traveler_ready">
                        <?php echo $_smarty_tpl->getSubTemplate ("_user-profile-nav.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                        </nav>
                    </aside>
                </div>
                <div class="col-md-9" id="user-profile-container">
                  <?php echo $_smarty_tpl->getSubTemplate ("_user-profile-overview.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                  <?php $_smarty_tpl->tpl_vars['tpl'] = new Smarty_variable(return_if_empty($_smarty_tpl->tpl_vars['scope']->value['view'],'_user-profile-overview.htm'), null, 0);?>
                  <?php if (($_smarty_tpl->tpl_vars['tpl']->value)) {?>
                  <?php echo $_smarty_tpl->getSubTemplate (((string)$_smarty_tpl->tpl_vars['tpl']->value), $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                  <?php } else { ?>
                  No tpl
                  <?php }?>                  
                </div>
            </div>
        </div>



        <div class="gap"></div>

<?php }} ?>
