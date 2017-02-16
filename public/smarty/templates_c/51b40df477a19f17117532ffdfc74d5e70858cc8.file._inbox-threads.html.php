<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:06:03
         compiled from "/web/comps/php/apt-dev/smarty/templates/_inbox-threads.html" */ ?>
<?php /*%%SmartyHeaderCode:434792558551c169d2f5706-42699814%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '51b40df477a19f17117532ffdfc74d5e70858cc8' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_inbox-threads.html',
      1 => 1427904363,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '434792558551c169d2f5706-42699814',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c169d4cfcf5_39538594',
  'variables' => 
  array (
    'scope' => 0,
    'thread' => 0,
    'res' => 0,
    'rental_name' => 0,
    'in' => 0,
    'out' => 0,
    'label' => 0,
    'status' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c169d4cfcf5_39538594')) {function content_551c169d4cfcf5_39538594($_smarty_tpl) {?><?php if (!is_callable('smarty_modifier_truncate')) include '/usr/share/php/Smarty/plugins/modifier.truncate.php';
?>
        <?php if (($_smarty_tpl->tpl_vars['scope']->value['threads'])) {?>          
          <ul class="list thread-list panel">
          <?php  $_smarty_tpl->tpl_vars['thread'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['thread']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['threads']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['thread']->key => $_smarty_tpl->tpl_vars['thread']->value) {
$_smarty_tpl->tpl_vars['thread']->_loop = true;
?>     
          <?php if (($_smarty_tpl->tpl_vars['thread']->value['parent_type']=='reservation'&&$_smarty_tpl->tpl_vars['thread']->value['parent_id'])) {?>
            <?php $_smarty_tpl->tpl_vars['res'] = new Smarty_variable(smarty_get_object($_smarty_tpl->tpl_vars['thread']->value['parent_id'],"reservation"), null, 0);?>
            <?php $_smarty_tpl->tpl_vars['in'] = new Smarty_variable($_smarty_tpl->tpl_vars['res']->value->checkin, null, 0);?>
            <?php $_smarty_tpl->tpl_vars['out'] = new Smarty_variable($_smarty_tpl->tpl_vars['res']->value->checkout, null, 0);?>
            <?php $_smarty_tpl->tpl_vars['rental_name'] = new Smarty_variable($_smarty_tpl->tpl_vars['res']->value->apartment_name, null, 0);?>
            <?php $_smarty_tpl->tpl_vars['status'] = new Smarty_variable(smarty_get_object($_smarty_tpl->tpl_vars['res']->value->status,"res_status","name"), null, 0);?>
            <?php $_smarty_tpl->tpl_vars['label'] = new Smarty_variable(smarty_get_object($_smarty_tpl->tpl_vars['res']->value->status,"res_status","label"), null, 0);?>
          <?php } else { ?>
          <?php }?>
            <li class="panel-body thread js-thread thread--read" id="thread_85190875">
              <div class="row">
                <div class="col-sm-9 col-md-3 thread-author">
                  <div class="row row-table">
                    <div class="user-avatar col-md-5">
                      <a href="/profile/<?php echo $_smarty_tpl->tpl_vars['thread']->value['other_user_id'];?>
">
                        <img class="round" src='<?php echo user_photo($_smarty_tpl->tpl_vars['thread']->value['other_user_id'],"thumb");?>
'>
                      </a>
                    </div>
                    <div class="col-sm-7 thread-name">
                      <?php echo user_display_name($_smarty_tpl->tpl_vars['thread']->value['other_user_id']);?>

                      <br>
                      <span class="thread-date"><?php echo time_elapsed_human($_smarty_tpl->tpl_vars['thread']->value['created']);?>
</span>
                    </div>
                  </div>
                </div>
                <a href="/inbox/<?php echo $_smarty_tpl->tpl_vars['thread']->value['thread'];?>
" class="thread-link link-reset text-muted">
                  <div class="col-sm-7 col-md-5 col-lg-6 thread-body">
                    <span class="thread-subject">
                    <?php echo smarty_modifier_truncate(smarty_get_object($_smarty_tpl->tpl_vars['thread']->value['id'],"chat","message"),80,"...");?>

                    </span>
                    <div class="text-muted show-lg">
                    <?php if (($_smarty_tpl->tpl_vars['thread']->value['parent_type']=='reservation'&&$_smarty_tpl->tpl_vars['thread']->value['parent_id'])) {?>
                      <?php echo $_smarty_tpl->tpl_vars['rental_name']->value;?>
<br>
                      <?php echo print_time_range($_smarty_tpl->tpl_vars['in']->value,$_smarty_tpl->tpl_vars['out']->value);?>

                    <?php }?>
                    </div>
                  </div>
                </a>    
                <div class="col-sm-7 col-md-4 col-lg-3 thread-label">
                  <div class="row">
                    <div class="col-sm-12 col-md-6">
                        <span class="label label-<?php echo $_smarty_tpl->tpl_vars['label']->value;?>
"><?php echo $_smarty_tpl->tpl_vars['status']->value;?>
</span>
                        <br>
                        <span class="hide-sm"><?php echo currency2html($_smarty_tpl->tpl_vars['res']->value->currency);?>
<?php echo round($_smarty_tpl->tpl_vars['res']->value->grand_total);?>
</span>
                    </div>
                    <div class="col-sm-6 options thread-actions hide-sm" id="options_85190875">
                      <ul class="thread-actions list-unstyled">
                        <li class="row-space-1">
                          <a class="link-reset thread-action js-star-thread " href="#" data-thread-id="85190875">
                            <i class="icon icon-star icon-beach"></i>
                            <i class="icon icon-star-alt icon-gray"></i>
                            <span class="thread-unstar">
                              Unstar
                            </span>
                            <span class="thread-star">
                              Star
                            </span>
                          </a>
                        </li>
                        <li id="thread_85190875_hidden">
                          <a class="link-reset thread-action js-archive-thread " href="#" data-thread-id="85190875">
                            <i class="icon icon-archive icon-gray"></i>
                            Archive
                          </a>
                        </li>
                      </ul>
                    </div>
                  </div>
                </div>
              </div>
            </li>
          <?php } ?>
          </ul>          
        <?php } else { ?>
        <h4>You do not have any messages yet</h4>
        <?php }?>


<?php }} ?>
