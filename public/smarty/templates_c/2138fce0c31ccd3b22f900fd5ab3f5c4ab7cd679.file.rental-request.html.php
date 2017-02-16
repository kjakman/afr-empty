<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 16:02:30
         compiled from "/web/comps/php/apt-dev/smarty/templates/rental-request.html" */ ?>
<?php /*%%SmartyHeaderCode:1747046910551c163939cb72-46631231%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '2138fce0c31ccd3b22f900fd5ab3f5c4ab7cd679' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/rental-request.html',
      1 => 1427904150,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1747046910551c163939cb72-46631231',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c1639620c49_56561884',
  'variables' => 
  array (
    'scope' => 0,
    'type' => 0,
    'title' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c1639620c49_56561884')) {function content_551c1639620c49_56561884($_smarty_tpl) {?>
        <div class="gap"></div>    
        

        <?php $_smarty_tpl->tpl_vars['paypal'] = new Smarty_variable(1, null, 0);?>
        <?php $_smarty_tpl->tpl_vars['bitcoin'] = new Smarty_variable(1, null, 0);?>
        
        <?php $_smarty_tpl->tpl_vars['type'] = new Smarty_variable($_smarty_tpl->tpl_vars['scope']->value['type'], null, 0);?>
        <?php $_smarty_tpl->tpl_vars['book_now'] = new Smarty_variable($_smarty_tpl->tpl_vars['type']->value==@constant('RES_TYPE_DIRECT') ? 1 : 0, null, 0);?>
        <?php $_smarty_tpl->tpl_vars['show_payment'] = new Smarty_variable($_smarty_tpl->tpl_vars['type']->value==@constant('RES_TYPE_INQUIRY') ? 0 : 1, null, 0);?>
        <?php $_smarty_tpl->tpl_vars['title'] = new Smarty_variable("Contact Host", null, 0);?>

        <h2><?php echo $_smarty_tpl->tpl_vars['title']->value;?>
</h2>
        
        <?php if (($_smarty_tpl->tpl_vars['scope']->value['error'])) {?>
        <div class="alert alert-danger" role="alert">
          <span class="glyphicon glyphicon-exclamation-sign" aria-hidden="true"></span>
          <span class="sr-only">Error:</span>
          <?php echo $_smarty_tpl->tpl_vars['scope']->value['error'];?>

        </div>    
        <?php } else { ?>
      <form id="payment-form" class="ajax-submit" data-handler="rental-inquiry">
        <input type="text" name="type" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['type'];?>
" />
        <input type="text" name="obj_type" value="reservation" />
        <input type="text" name="res_id" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['reservation']['res_id'];?>
" />
        
        <div class="container">
          <div class="row">
            <div class="col-md-8">
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
                  <h4>Ask a question to <?php echo user_display_name($_smarty_tpl->tpl_vars['scope']->value['reservation']['host_id']);?>
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
              <input class="btn btn-primary" type="submit" value=" Send Inquiry " />

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
