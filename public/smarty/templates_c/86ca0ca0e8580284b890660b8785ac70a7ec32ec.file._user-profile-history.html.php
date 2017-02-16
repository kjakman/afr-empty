<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:05:34
         compiled from "/web/comps/php/apt-dev/smarty/templates/_user-profile-history.html" */ ?>
<?php /*%%SmartyHeaderCode:756193507551c17435d90f4-93050748%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '86ca0ca0e8580284b890660b8785ac70a7ec32ec' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_user-profile-history.html',
      1 => 1427904334,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '756193507551c17435d90f4-93050748',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c17436bb149_95057792',
  'variables' => 
  array (
    'scope' => 0,
    'reservation' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c17436bb149_95057792')) {function content_551c17436bb149_95057792($_smarty_tpl) {?>
                    <div class="checkbox">
                        <label>               
                            <input class="i-check" type="checkbox" />Show only current trip</label>
                    </div>
                    <table class="table table-bordered table-striped table-booking-history">
                        <thead>       
                            <tr>
                                <th>Type</th>
                                <th>ID</th>
                                <th>Title</th>
                                <th>Location</th>
                                <th>Order Date</th>
                                <th>Travel Dates</th>
                                <th>Cost</th>
                                <th>Status</th>
                                <th>Chat</th>
                                <th>Actions</th>
                            </tr>
                        </thead>
                        <tbody>
                        <?php  $_smarty_tpl->tpl_vars['reservation'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['reservation']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['reservations']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['reservation']->key => $_smarty_tpl->tpl_vars['reservation']->value) {
$_smarty_tpl->tpl_vars['reservation']->_loop = true;
?>
                            <tr>
                                <td class="booking-history-type"><i class="fa fa-home"></i><small>rental</small>
                                </td>
                                <td><a href="/booking-status/<?php echo $_smarty_tpl->tpl_vars['reservation']->value['res_id'];?>
"><?php echo $_smarty_tpl->tpl_vars['reservation']->value['res_id'];?>
</td>
                                <td class="booking-history-title"><?php echo $_smarty_tpl->tpl_vars['reservation']->value['apartment_name'];?>
</td>
                                <td><?php echo cityname($_smarty_tpl->tpl_vars['reservation']->value['city_id']);?>
</td>
                                <td><?php echo sql2human($_smarty_tpl->tpl_vars['reservation']->value['created']);?>
</td>
                                <td><?php echo sql2human($_smarty_tpl->tpl_vars['reservation']->value['checkin']);?>
 <i class="fa fa-long-arrow-right"></i> <?php echo sql2human($_smarty_tpl->tpl_vars['reservation']->value['checkout']);?>
</td>
                                <td><?php echo currency2html($_smarty_tpl->tpl_vars['reservation']->value['currency']);?>
<?php echo $_smarty_tpl->tpl_vars['reservation']->value['grand_total'];?>
</td>
                                <td class="text-center" style="color:#<?php echo smarty_get_object($_smarty_tpl->tpl_vars['reservation']->value['status'],'res_status','color');?>
"><?php echo smarty_get_object($_smarty_tpl->tpl_vars['reservation']->value['status'],"res_status","name");?>
</i></td>
                                <td><?php echo $_smarty_tpl->tpl_vars['reservation']->value['chat_count'];?>
</i></td>
                                <td class="text-center"></td>
                            </tr>
                        <?php } ?>
                        </tbody>
                    </table>


<?php }} ?>
