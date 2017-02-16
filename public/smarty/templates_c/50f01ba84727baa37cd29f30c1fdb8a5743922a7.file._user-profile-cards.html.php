<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:20:55
         compiled from "/web/comps/php/apt-dev/smarty/templates/_user-profile-cards.html" */ ?>
<?php /*%%SmartyHeaderCode:1751680928551c1741e8a689-23870314%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '50f01ba84727baa37cd29f30c1fdb8a5743922a7' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_user-profile-cards.html',
      1 => 1427905255,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1751680928551c1741e8a689-23870314',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c1741ee2408_49093915',
  'variables' => 
  array (
    'scope' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c1741ee2408_49093915')) {function content_551c1741ee2408_49093915($_smarty_tpl) {?>
                    <div class="mfp-with-anim mfp-hide mfp-dialog" id="edit-card-dialog">
                        <h3 class="mb0">Edit Card</h3>
                        <form id="cc-edit-form" class="cc-form ajax-submit" data-validator="cc_validator" data-handler="edit-user-cc">
                            <input name="remember" type="hidden" value="1" />                       
                            <?php echo $_smarty_tpl->getSubTemplate ("_credit-card-form.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                            <div class="checkbox">
                                <label><input name="default_card" value="1" class="i-check" type="checkbox" checked/>Set as primary</label>
                            </div>
                            <input class="btn btn-primary" type="submit" value="Add Card" />

                        </form>
               
                    </div>
                    <div class="mfp-with-anim mfp-hide mfp-dialog" id="new-card-dialog">
                        <h3>New Card</h3>
                        <form id="cc-add-form" class="cc-form ajax-submit" data-validator="cc_validator" data-handler="add-user-cc" data-handler_options='{"reload": "1"}'>
                        
                            <input name="remember" type="hidden" value="1" />
                            <?php echo $_smarty_tpl->getSubTemplate ("_credit-card-form.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                            <div class="checkbox">
                                <label><input name="default_card" value="1" class="i-check" type="checkbox" checked/>Set as primary</label>
                            </div>
                            <input class="btn btn-primary" type="submit" value="Add Card" />
                            
                        </form>
                    </div>
                    <div class="row row-wrap">
                      <?php  $_smarty_tpl->tpl_vars['card'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['card']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['cards']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['card']->key => $_smarty_tpl->tpl_vars['card']->value) {
$_smarty_tpl->tpl_vars['card']->_loop = true;
?>
                        <?php echo $_smarty_tpl->getSubTemplate ("_credit-card.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                      <?php } ?>

                        <div class="col-md-4"><a class="card-thumb popup-text" href="#new-card-dialog" data-effect="mfp-zoom-out"><i class="fa fa-plus card-thumb-new"></i><p >add new card</p></a>
                        </div>
                    </div>
                </div>


<?php }} ?>
