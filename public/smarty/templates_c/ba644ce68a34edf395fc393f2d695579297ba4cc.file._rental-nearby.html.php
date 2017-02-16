<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 09:20:20
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-nearby.html" */ ?>
<?php /*%%SmartyHeaderCode:1617071108551ba8d900e6e5-03821512%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'ba644ce68a34edf395fc393f2d695579297ba4cc' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-nearby.html',
      1 => 1427880020,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1617071108551ba8d900e6e5-03821512',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551ba8d90ab9d1_75921288',
  'variables' => 
  array (
    'apt' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551ba8d90ab9d1_75921288')) {function content_551ba8d90ab9d1_75921288($_smarty_tpl) {?>
                                
                                    <div class="booking-item booking-item-small">                                
                                        <div class="row">
                                            <div class="col-xs-4">
                                                <img src="<?php echo get_media_source($_smarty_tpl->tpl_vars['apt']->value['media'],'small');?>
" alt="<?php echo $_smarty_tpl->tpl_vars['apt']->value['name'];?>
" title="<?php echo $_smarty_tpl->tpl_vars['apt']->value['name'];?>
" />
                                            </div>
                                            <div class="col-xs-5">
                                                <h5 class="booking-item-title"><?php echo $_smarty_tpl->tpl_vars['apt']->value['name'];?>
</h5>
                                                <input type="number" readonly class="rating" 
                                                   value="<?php echo $_smarty_tpl->tpl_vars['apt']->value['review_score'];?>
"
                                                   data-min="0" data-max="10"
                                                   data-size="xxs" data-show-clear="false"
                                                   data-show-caption="false">
                                            </div>
                                            <div class="col-xs-3"><span class="booking-item-price"><?php echo currency2html($_smarty_tpl->tpl_vars['apt']->value['currency']);?>
<?php echo $_smarty_tpl->tpl_vars['apt']->value['rate_day'];?>
</span><br><?php echo sprintf("%.1f",$_smarty_tpl->tpl_vars['apt']->value['distance']);?>
km
                                            </div>
                                        </div>
                                    </div>


<?php }} ?>
