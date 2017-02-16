<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:01:14
         compiled from "/web/comps/php/apt-dev/smarty/templates/rental-inquiry-success.html" */ ?>
<?php /*%%SmartyHeaderCode:744019684551c164a7ae8c9-50047975%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '7b4786794e5b398c9d20e6662bc11ed6c60ab689' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/rental-inquiry-success.html',
      1 => 1427904074,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '744019684551c164a7ae8c9-50047975',
  'function' => 
  array (
  ),
  'variables' => 
  array (
    'user' => 0,
  ),
  'has_nocache_code' => false,
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c164a7e15c1_04652163',
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c164a7e15c1_04652163')) {function content_551c164a7e15c1_04652163($_smarty_tpl) {?>


        <div class="gap"></div>


        <div class="container">
            <div class="row">
                <div class="col-md-8 col-md-offset-2">
                    <i class="fa fa-check round box-icon-large box-icon-center box-icon-success mb30"></i>	
                    <h2 class="text-center"><?php echo $_smarty_tpl->tpl_vars['user']->value['display_name_short'];?>
, your inquriy has been sent!</h2>
                    <h5 class="text-center mb30">A copy of your inquiry details has been send to <?php echo $_smarty_tpl->tpl_vars['user']->value['email_address'];?>
</h5>
                    <ul class="order-payment-list list mb30">
                        <li>
                            <div class="row">
                                <div class="col-xs-9">
                                    <h5><i class="fa fa-plane"></i> Flight from London to New York City</h5>
                                    <p><small>April 24, 2014</small>
                                    </p>
                                </div>
                                <div class="col-xs-3">
                                    <p class="text-right"><span class="text-lg">$150</span>
                                    </p>
                                </div>
                            </div>
                        </li>
                        <li>
                            <div class="row">
                                <div class="col-xs-9">
                                    <h5><i class="fa fa-plane"></i> Flight from New York City to London</h5>
                                    <p><small>April 28, 2014</small>
                                    </p>
                                </div>
                                <div class="col-xs-3">
                                    <p class="text-right"><span class="text-lg">$187</span>
                                    </p>
                                </div>
                            </div>
                        </li>
                    </ul>
                    <h4 class="text-center">You might also need in New York</h4>
                    <ul class="list list-inline list-center">
                        <li><a class="btn btn-primary" href="#"><i class="fa fa-building-o"></i> Hotels</a>
                            <p class="text-center lh1em mt5"><small>398 offers<br /> from $139</small>
                            </p>
                        </li>
                        <li><a class="btn btn-primary" href="#"><i class="fa fa-home"></i> Rentlas</a>
                            <p class="text-center lh1em mt5"><small>229 offers<br /> from $143</small>
                            </p>
                        </li>
                        <li><a class="btn btn-primary" href="#"><i class="fa fa-dashboard"></i> Cars</a>
                            <p class="text-center lh1em mt5"><small>180 offers<br /> from $73</small>
                            </p>
                        </li>
                        <li><a class="btn btn-primary" href="#"><i class="fa fa-bolt"></i> Activities</a>
                            <p class="text-center lh1em mt5"><small>274 offers<br /> from $131</small>
                            </p>
                        </li>
                    </ul>
                </div>
            </div>
            <div class="gap"></div>
        </div>




<?php }} ?>
