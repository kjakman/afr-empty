<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:59:30
         compiled from "/web/comps/php/apt-dev/smarty/templates/rental-payment.html" */ ?>
<?php /*%%SmartyHeaderCode:1694777273551c126c3c6d01-23150800%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'f90ef071d8bca9a7ceb68e9d2e7d55098440003e' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/rental-payment.html',
      1 => 1427903970,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1694777273551c126c3c6d01-23150800',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c126c70f804_95902658',
  'variables' => 
  array (
    'scope' => 0,
    'type' => 0,
    'book_now' => 0,
    'title' => 0,
    'paypal' => 0,
    'bitcoin' => 0,
    'action' => 0,
    'card' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c126c70f804_95902658')) {function content_551c126c70f804_95902658($_smarty_tpl) {?><?php if (!is_callable('smarty_modifier_capitalize')) include '/usr/share/php/Smarty/plugins/modifier.capitalize.php';
?>
        <div class="gap"></div>    
        <?php $_smarty_tpl->tpl_vars['type'] = new Smarty_variable($_smarty_tpl->tpl_vars['scope']->value['reservation']['type'], null, 0);?>
        <?php $_smarty_tpl->tpl_vars['book_now'] = new Smarty_variable($_smarty_tpl->tpl_vars['type']->value==@constant('RES_TYPE_DIRECT') ? 1 : 0, null, 0);?>
        
        <?php if (($_smarty_tpl->tpl_vars['book_now']->value)) {?>
        <?php $_smarty_tpl->tpl_vars['action'] = new Smarty_variable("pay", null, 0);?>
        <?php $_smarty_tpl->tpl_vars['paypal'] = new Smarty_variable(1, null, 0);?>
        <?php $_smarty_tpl->tpl_vars['bitcoin'] = new Smarty_variable(1, null, 0);?>
        <?php $_smarty_tpl->tpl_vars['title'] = new Smarty_variable("Payment", null, 0);?>
        <?php } else { ?>
        <?php $_smarty_tpl->tpl_vars['paypal'] = new Smarty_variable(0, null, 0);?>
        <?php $_smarty_tpl->tpl_vars['bitcoin'] = new Smarty_variable(0, null, 0);?>
        <?php $_smarty_tpl->tpl_vars['action'] = new Smarty_variable("authorize", null, 0);?>
        <?php $_smarty_tpl->tpl_vars['title'] = new Smarty_variable("Payment Authorization", null, 0);?>
        <?php }?>
        <h2><?php echo $_smarty_tpl->tpl_vars['title']->value;?>
</h2>
        
        <?php if (($_smarty_tpl->tpl_vars['scope']->value['error'])) {?>
        <div class="alert alert-danger" role="alert">
          <span class="glyphicon glyphicon-exclamation-sign" aria-hidden="true"></span>
          <span class="sr-only">Error:</span>
          <?php echo $_smarty_tpl->tpl_vars['scope']->value['error'];?>

        </div>    
        <?php } else { ?>
      <form id="payment-form" class="ajax-submit cc-form" data-validator="cc_validator" data-handler="rental-payment">
        <div class="container">
          <div class="row">
            <div class="col-md-8">
              <div class="row">
              <input type="text" name="type" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['type'];?>
" />
              <input type="text" name="inv_id" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['inv_id'];?>
" />
              <input type="text" name="cc_id" value="" />
              <input type="text" name="payment_type" value="10" />
              <input type="text" name="parent_type" value="reservation" />
              <input type="text" name="payment_action" value="<?php if (($_smarty_tpl->tpl_vars['book_now']->value)) {?>Sale<?php } else { ?>Authorization<?php }?>" />
              <input type="text" name="parent_id" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['res_id'];?>
" />
              <input type="text" name="currency" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['currency'];?>
" />
              <input type="text" name="amount" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['grand_total'];?>
" />
                
              <div class="col-md-6">
              <?php if (($_smarty_tpl->tpl_vars['paypal']->value)) {?>
                <img class="pp-img" src="/traveler/img/paypal.png" alt="Image Alternative text" title="Image Title" />
                <p>Important: You will be redirected to PayPal's website to securely complete your payment.</p>
                <a class="btn btn-primary"><i class="fa fa-paypal"></i> Pay with Paypal</a>	
                <div class="gap gap-small"></div>
              <?php }?>
              <?php if (($_smarty_tpl->tpl_vars['bitcoin']->value)) {?>
                <img class="pp-img" src="/traveler/img/bitcoin.png" alt="Image Alternative text" title="Image Title" />
                <p>Important: You will be redirected to BitPay's website to securely complete your payment.</p>
                <a class="btn btn-primary"><i class="fa fa-bitcoin"></i> Pay with Bitcoin</a>	
                <div class="gap gap-small"></div>
              <?php }?>
              
              <?php if (($_smarty_tpl->tpl_vars['scope']->value['cards'])) {?>
                <h4><?php echo smarty_modifier_capitalize($_smarty_tpl->tpl_vars['action']->value);?>
 with existing card</h4>
                <ul class="card-select">
                  <?php  $_smarty_tpl->tpl_vars['card'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['card']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['cards']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['card']->key => $_smarty_tpl->tpl_vars['card']->value) {
$_smarty_tpl->tpl_vars['card']->_loop = true;
?>
                  <li data-id="<?php echo $_smarty_tpl->tpl_vars['card']->value['id'];?>
">
                    <img class="card-select-img" src="<?php echo $_smarty_tpl->tpl_vars['card']->value['image'];?>
" alt="Image Alternative text" title="Image Title" />
                    <div class="card-select-data">
                      <p class="<?php if (($_smarty_tpl->tpl_vars['card']->value['expired'])) {?>text-danger <?php }?>card-select-number"><?php echo $_smarty_tpl->tpl_vars['card']->value['number'];?>
</p>
                      <?php if (($_smarty_tpl->tpl_vars['card']->value['expired'])) {?>
                      <span>(Expired)</span>                
                      <?php } else { ?>
                      <input name="cvc-<?php echo $_smarty_tpl->tpl_vars['card']->value['id'];?>
" class="form-control card-select-cvc" type="text" placeholder="CVC" />
                      <?php }?>
                    </div>
                  </li>
                  <?php } ?>
                </ul>
              <?php }?>
              </div>
              
              <div class="col-md-6">
                <h4><?php echo smarty_modifier_capitalize($_smarty_tpl->tpl_vars['action']->value);?>
 with new Card</h4>
                  <?php $_smarty_tpl->tpl_vars['dummy'] = new Smarty_variable($_SESSION['test_payments'], null, 0);?>
                  <?php echo $_smarty_tpl->getSubTemplate ("_credit-card-form.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                
                <h4>Billing address</h4>
                  <?php echo $_smarty_tpl->getSubTemplate ("_address-form.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                  <div class="checkbox checkbox-small">
                    <label>
                      <input name="remember" class="i-check" type="checkbox" checked/>Add to My Cards</label>
                  </div>
                </div>
              </div><!-- row -->
              <div class="gap"></div>
              <div class="row">
                <div class="col-md-2 user-avatar-big">
                  <a href="/profile/<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['host_id'];?>
">
                    <img class="origin round" src="<?php echo user_photo($_smarty_tpl->tpl_vars['scope']->value['reservation']['host_id'],'thumb');?>
" 
                         title="<?php echo user_display_name($_smarty_tpl->tpl_vars['scope']->value['reservation']['host_id']);?>
">
                  </a>                      
                </div>
                <div class="col-md-10">                    
                  <h4>Introduce yourself to <?php echo user_display_name($_smarty_tpl->tpl_vars['scope']->value['reservation']['host_id']);?>
</h4>
                  <textarea class="form-control" name="extra_info" placeholder="Your personal message to the host here..."></textarea>                 
                </div>
              </div><!-- row -->
              
              <div class="gap gap-small"></div>
              <ul class="list">
                <li>You will only be charged if the host accepts your request. They’ll have 24 hours to reply.</li>
                <li>If the host declines or does not respond, no charge is made.</li>
                <li>By clicking on "Request to Book", you agree to pay the total amount shown in the summary on the right, 
                which includes <a href="#">Occupancy Taxes and Service Fees</a>, and to follow the <a href="#">Terms of Service</a>, 
                <a href="#">House Rules</a>, <a href="#">Cancellation Policy</a> and <a href="#">Guest Refund Policy</a>.</li>
              </ul>
              <div class="gap gap-small"></div>
              <input class="btn btn-primary" type="submit" value=" Request to Book " />

            </div><!-- outer col-md-8 -->
    
            <div class="col-md-4">
              <div class="booking-item-payment">
                <header class="clearfix">
                  <a class="booking-item-payment-img" href="#">
                    <img src="<?php echo get_media_source($_smarty_tpl->tpl_vars['scope']->value['property']['media']);?>
" alt="Image Alternative text" title="hotel 1" />
                  </a>
                  <h5 class="booking-item-payment-title"><a href="#"><?php echo $_smarty_tpl->tpl_vars['scope']->value['property']['name'];?>
</a></h5>
                  <ul class="icon-group booking-item-rating-stars">
                    <li><i class="fa fa-star"></i>
                    </li>
                    <li><i class="fa fa-star"></i>
                    </li>
                    <li><i class="fa fa-star"></i>
                    </li>
                    <li><i class="fa fa-star"></i>
                    </li>
                    <li><i class="fa fa-star"></i>
                    </li>
                  </ul>
                </header>
                <ul class="booking-item-payment-details">
                  <li>
                    <h5>Booking for <?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['num_days'];?>
 <?php if (($_smarty_tpl->tpl_vars['scope']->value['reservation']['num_days']==1)) {?>day<?php } else { ?>days<?php }?></h5>
                    <div class="booking-item-payment-date">
                      <p class="booking-item-payment-date-day">April, 26</p>
                      <p class="booking-item-payment-date-weekday">Saturday</p>
                    </div><i class="fa fa-arrow-right booking-item-payment-date-separator"></i>
                    <div class="booking-item-payment-date">
                      <p class="booking-item-payment-date-day">May, 3</p>
                      <p class="booking-item-payment-date-weekday">Saturday</p>
                    </div>
                  </li>
                  <li>
                    <h5>Property (<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['num_guests'];?>
 <?php if (($_smarty_tpl->tpl_vars['scope']->value['reservation']['num_guests']==1)) {?>guest<?php } else { ?>guests<?php }?>)</h5>
                    <ul class="booking-item-payment-price">
                      <li>
                        <p class="booking-item-payment-price-title"><?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['num_days'];?>
 <?php if (($_smarty_tpl->tpl_vars['scope']->value['reservation']['num_days']==1)) {?>day<?php } else { ?>days<?php }?></p>
                        <p class="booking-item-payment-price-amount"><?php echo currency2html($_smarty_tpl->tpl_vars['scope']->value['reservation']['currency']);?>
 <?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['rate_base'];?>
<small>/<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['rate_type'];?>
</small>
                        </p>
                      </li>
                      <li>
                        <p class="booking-item-payment-price-title">Fees</p>
                        <p class="booking-item-payment-price-amount"><?php echo currency2html($_smarty_tpl->tpl_vars['scope']->value['reservation']['currency']);?>
 <?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['fees'];?>
</p>
                      </li>                  
                      <li>
                        <p class="booking-item-payment-price-title">Taxes</p>
                        <p class="booking-item-payment-price-amount"><?php echo currency2html($_smarty_tpl->tpl_vars['scope']->value['reservation']['currency']);?>
 <?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['city_tax'];?>

                        </p>
                      </li>
                    </ul>
                  </li>
                </ul>
                <p class="booking-item-payment-total">Total trip: <span><?php echo currency2html($_smarty_tpl->tpl_vars['scope']->value['reservation']['currency']);?>
 <?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['grand_total'];?>
</span>
                </p>
              </div>
            </div>
          </div>
          <div class="gap"></div>
        </div>
      </form>
    
        <?php }?>


<?php }} ?>
