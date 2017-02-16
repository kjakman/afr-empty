<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:08:12
         compiled from "/web/comps/php/apt-dev/smarty/templates/rental-edit.html" */ ?>
<?php /*%%SmartyHeaderCode:1035428258551bac7fd358f0-67344242%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '7e1e0c1d34b424a5ad5fd95ec6e4f1c3c53c94fa' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/rental-edit.html',
      1 => 1427900892,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1035428258551bac7fd358f0-67344242',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551bac7fe35aa8_47062037',
  'variables' => 
  array (
    'scope' => 0,
    'tpl' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551bac7fe35aa8_47062037')) {function content_551bac7fe35aa8_47062037($_smarty_tpl) {?>

        <div class="container">
            <h1 class="page-title">Edit Rental</h1>
        </div>




        <div class="container">
            <div class="row">
                <div class="col-md-3">
                    <aside class="user-profile-sidebar">
                        <div class="user-profile-avatar text-center">
                            <img src="<?php echo return_if_empty(get_media_source($_smarty_tpl->tpl_vars['scope']->value['media'],'small'),'/traveler/img/800x600.png');?>
" alt="<?php echo $_smarty_tpl->tpl_vars['scope']->value['name'];?>
" title="AMaze" />
                            <h5><a href="<?php echo $_smarty_tpl->tpl_vars['scope']->value['property_link'];?>
" ><?php echo $_smarty_tpl->tpl_vars['scope']->value['name'];?>
</a></h5>
                            <p>Listed Since <?php echo sql2human($_smarty_tpl->tpl_vars['scope']->value['created']);?>
</p>
                        </div>
                        <nav data-target="#rental-edit-container" 
                             data-controller="rental_edit" 
                             data-data='<?php echo json_encode($_smarty_tpl->tpl_vars['scope']->value['data']);?>
'
                             data-success_handler="traveler_ready">
                        <?php echo $_smarty_tpl->getSubTemplate ("_rental-edit-nav.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                        </nav>
                    </aside>
                </div>
                <div class="col-md-9" id="rental-edit-container">
                  <?php echo $_smarty_tpl->getSubTemplate ("_rental-edit-overview.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                  <?php $_smarty_tpl->tpl_vars['tpl'] = new Smarty_variable(return_if_empty($_smarty_tpl->tpl_vars['scope']->value['view'],'_rental-edit-overview.html'), null, 0);?>
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
