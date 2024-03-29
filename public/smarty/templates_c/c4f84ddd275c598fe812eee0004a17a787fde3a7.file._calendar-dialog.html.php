<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:05:28
         compiled from "/web/comps/php/apt-dev/smarty/templates/_calendar-dialog.html" */ ?>
<?php /*%%SmartyHeaderCode:89602320754dc83a8f1a807-46507427%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'c4f84ddd275c598fe812eee0004a17a787fde3a7' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_calendar-dialog.html',
      1 => 1427900728,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '89602320754dc83a8f1a807-46507427',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_54dc83a900e787_93365387',
  'variables' => 
  array (
    'scope' => 0,
    'id' => 0,
    'name' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_54dc83a900e787_93365387')) {function content_54dc83a900e787_93365387($_smarty_tpl) {?>
<div id="overlay_content" class="modal fade" tabindex="-1" data-replace="true">
  <form class="form-horizontal ajax-submit" id="calendar_dialog_form" data-handler="save" data-success_handler="calendar_reload">
  <div class="modal-header">
    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
    <b id="overlay_title"><?php echo return_if_empty($_smarty_tpl->tpl_vars['scope']->value['title'],"New Reservation");?>
</b>
  </div>
  <div class="modal-body" class="container-fluid">
    <div role="tabpanel">
      <!-- Nav tabs -->
      <ul class="nav nav-tabs" role="tablist" id="cal_dialog_tabs">
        <li role="presentation" class="active"><a href="#tab1" aria-controls="name" role="tab" data-toggle="tab">Name</a></li>
        <li role="presentation"><a href="#tab2" aria-controls="rate" role="tab" data-toggle="tab">Rate</a></li>
        <li role="presentation"><a href="#tab3" aria-controls="address" role="tab" data-toggle="tab">Address</a></li>
        <li role="presentation"><a href="#tab4" aria-controls="notes" role="tab" data-toggle="tab">Notes</a></li>
      </ul>
      <br>
    
      <!-- Tab panes -->
      <div class="tab-content">
        <div role="tabpanel" class="tab-pane active" id="tab1">
          <input type="hidden" name='site_id'>
          <input type="hidden" name='user_id'>
          <input type="hidden" name='res_id' id='res_id'>
          <input type="hidden" name='id' id='obj_id'>
          <input type="hidden" name='obj_type' id='obj_type'>
          <input type="hidden" name='rate_class' id='rate_class'>
          <input type="hidden" name='rate_package' id='rate_package'>
          <input type="hidden" name='num_packages' id='num_packages'>
          <input type="hidden" name='package_unit' id='package_unit'>
          <input type="hidden" name='num_months' id='num_months'>
          <input type="hidden" name='rate_day' id='rate_day'>
          <input type="hidden" name='rate_hour' id='rate_hour'>
          <input type="hidden" name='rate_extraperson' id='rate_extraperson'>
          <input type="hidden" name='currency' id='currency'>
          <input type="hidden" name='address_id' id='address_id'>
          <input type="hidden" name='fees' id='fees'>
          <input type="hidden" name='city_tax' id='city_tax'>
          <input type="hidden" name='city_id' id='city_id'>
          <input type="hidden" name='property_type' id='property_type'>
          <input type="hidden" name='type' id='type'>
          <input type="hidden" name='grand_total_new_res' id='grand_total_new_res'>
          <input type="hidden" name="num_hours" id="num_hours" >
          <input type="hidden" name="num_days" id="num_days" >
          <input type="hidden" name="num_months" id="num_months" >
          <input type="hidden" name="apartment_name" id="apartment_name" >
          
          
          <!-- 1st line -->
          <div class="col-sm-6">
            <div class='form-group'>
              <label for='status'>Status</label>
              <select id='status' name='status' class="form-control">
                <option value='10' selected='selected'>Unconfirmed</option>
                <option value='15'>Proposed</option>
                <option value='30'>Reserved</option>
              </select>
            </div>
          </div>
          <div class="col-sm-6">
            <div class='form-group'>
              <label for='apt_id'>Apartment</label>
              <select id='apt_id'  name='apt_id' onchange='update_overlay_rate();' class="form-control">
                <option value='0'>Select...</option>
                <?php  $_smarty_tpl->tpl_vars['name'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['name']->_loop = false;
 $_smarty_tpl->tpl_vars['id'] = new Smarty_Variable;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['cal_params']['apts']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['name']->key => $_smarty_tpl->tpl_vars['name']->value) {
$_smarty_tpl->tpl_vars['name']->_loop = true;
 $_smarty_tpl->tpl_vars['id']->value = $_smarty_tpl->tpl_vars['name']->key;
?>
                <option value='<?php echo $_smarty_tpl->tpl_vars['id']->value;?>
'><?php echo $_smarty_tpl->tpl_vars['name']->value;?>
</option>
                <?php } ?>
              </select>
            </div>
          </div>
          
          <!-- 2nd line -->
          <div class="col-sm-2">
            <div class='form-group'>  
              <label for='salutation'>Mr/Ms</label>
              <select id='salutation'  name='salutation' class="form-control">
                <option value='' selected='selected'></option>
                <option value='Mr.'>Mr.</option>
                <option value='Ms.'>Ms.</option>
                <option value='Mrs.'>Mrs.</option>
                <option value='Dr.'>Dr.</option>
              </select>
            </div>
          </div>
          
          <div class="col-sm-4">
            <div class='form-group'>
              <label for='first_name'>First</label>
              <input size='10' name='first_name' type='text' id='first_name' maxlength='50' class='form-control'>
            </div>
          </div>
          
          <div class="col-sm-4">
            <div class='form-group'>
              <label for='last_name'>Last</label>
              <input size='16' name='last_name' type='text' id='last_name' maxlength='50' class='form-control'>
            </div>
          </div>
          
          <div class="col-sm-2">
            <div class='form-group '>
              <label for='num_guests'>Guests</label>
              <select id='num_guests'  name='num_guests' onchange='update_overlay_rate()' class='form-control'>
                <option value='1' selected='selected'>1</option>
                <option value='2'>2</option>
                <option value='3'>3</option>
                <option value='4'>4</option>
                <option value='5'>5</option>
                <option value='6'>6</option>
              </select>
            </div>
          </div>          

          <!-- 3rd line -->
          <div class="col-sm-4">
            <div class='form-group'>
              <label for='first_name'>Phone</label>
              <input size='20' name='cell_phone' type='text' id='cell_phone' maxlength='50' class='form-control'>
            </div>
          </div>
          
          <div class="col-sm-4">
            <div class='form-group'>
              <label for='last_name'>Email</label>
              <input size='20' name='email_address' type='text' id='email_address' maxlength='50' class='form-control'>
            </div>
          </div>

          <div class="col-sm-4">
            <div class='checkbox'>
              <label for='last_name'>Send mail?</label>
              <input name='send_email' type="checkbox" class="bootstrap-toggle" <?php if (($_smarty_tpl->tpl_vars['scope']->value['send_mail'])) {?>checked<?php }?> data-toggle="toggle" data-onstyle="success" data-offstyle="danger">                            
            </div>
          </div>

          <!-- 4th line -->
          <div class="row">
            <div class="col-sm-8" id="dialog_period">
              <div class="input-daterange input-group">
                <label for='checkin'>Checkin</label>
                <input type="text" class="input-sm form-control" name="checkin" onchange="update_overlay_period('in');" />
                <label for='checkout'>Checkout</label>
                <input type="text" class="input-sm form-control" name="checkout" onchange="update_overlay_period('out');" />
              </div>
            </div>
            <div class="col-sm-4" id="dialog_period">
              <label for='period'>&nbsp;</label>
              <span class="bold" id='overlay_period' ></span>
            </div>
          </div>
          
          <!-- 5th line -->
        
          <br><br>        
          <div class='dialog-total'>
            <a class='goto-tab' data-index='1' href='#cal_dialog_tab_Rate'>
              Rate: 
              <span class='currency_total reservation-rate'>0.00</span> / 
              <span class='currency_total reservation-rate_type'>??</span>
            </a> 
            <a class='discount_link goto-tab hidden' data-index='1' href='#cal_dialog_tab_Rate'> - Discount: 
              <span class='reservation-discount'></span>
            </a> 
            <a class='tax_link goto-tab hidden' data-index='1' href='#cal_dialog_tab_Tax'> + Tax: 
              <span class='currency_total reservation-tax'>0.00</span>
            </a>
            <a class='fee_link goto-tab hidden' data-index='2' href='#cal_dialog_tab_Fees'> + Fees: 
              <span class='currency_total reservation-fees'>0.00</span>
            </a> = 
            <span class='currency_total reservation-total'>0.00</span>   
            <span class='reservation-currency'></span>
          </div>
          
          <span id='special_rate'>Standard Rate</span>
          <span id='special_rate_lock' class='margin_left'></span>
          
        </div><!-- #tab1: name,dates -->
        <div role="tabpanel" class="tab-pane" id="tab2">

        
    <div class="form-group relative">
      <label for="rate_base" class="col-sm-3 control-label">Rate</label>
      <div class="col-sm-6">
        <input size='10' name='rate_base' type='text' id='rate_base' onchange='custom_rate();update_overlay_total()' autocomplete='off'>
        <b >/</b>
        <select id='rate_type' name='rate_type' onchange='update_overlay_rate_type()'>
          <option value='day'>Day</option>
          <option value='month'>Month</option>
          <option value='total'>Total</option>
        </select>  
      </div>
      <span class='abs_right'><label for='rate_locked'>Locked?</label>
        <input name='rate_locked' type="checkbox" value='1' id='rate_locked'>                            
      </span>
    </div>
    
    <div class="form-group relative">
      <label for="discount" class="col-sm-3 control-label">Discount</label>
      <div class="col-sm-6">
        <input name='discount' type='text' id='discount' onchange='lock_discount();update_overlay_total()' autocomplete='off'>
      </div>
      <span class='abs_right'><label for='discount_locked'>Locked?</label>
        <input name='discount_locked' type="checkbox" value='1' id='discount_locked'>
      </span>
    </div>

    <div class="form-group relative">
      <label for="commission" class="col-sm-3 control-label">Commission</label>
      <div class="col-sm-6">
        <input name='commission' type='text' id='commission' autocomplete='off'>
      </div>
      <span class='abs_right'><label for='monthly_billing'>Bill Monthly?</label>
        <input name='monthly_billing' type="checkbox" value='1' id='monthly_billing'>
      </span>
    </div>
    
    <div class="form-group relative">
      <label for="deposit_percentage" class="col-sm-3 control-label">Deposit</label>
      <div class="col-sm-6">
        <input name='deposit_percentage' type='text' id='deposit_percentage' autocomplete='off'>
      </div>
      <span class='abs_right'><label for='city_tax_rate'>Tax?</label>
        <input size='4' name='city_tax_rate' type='text' value='5%' id='city_tax_rate' onchange='update_overlay_total()' autocomplete='off'>
        <input name='charge_city_tax' type="checkbox" value='1' id='charge_city_tax' onchange='update_overlay_total()'>                            
      </span>
    </div>

          <div class='fieldset_div '>
            <label>City tax</label>
            <span class='currency_total reservation-tax'>0.00</span> 
            <span class='reservation-currency'></span>
          </div>
          <div class='fieldset_div '><label>Fees</label>
            <span class='currency_total reservation-fees'>0.00</span> 
            <span class='reservation-currency'></span>
          </div>
          <div class='fieldset_div '>
            <label>Total</label>
            <span class='currency_total reservation-total'>0.00</span> 
            <span class='reservation-currency'></span>
          </div>

        </div><!-- #tab2: Rate -->

        <div role="tabpanel" class="tab-pane" id="tab3">          
          <div class="col-sm-6">
            <div class='form-group'>
              <label for='address1'>Address</label>
              <input size='15' class='form-control' name='address1' type='text' id='address1' maxlength='50'>
            </div>
          </div>
          <div class="col-sm-6">
            <div class='form-group'>
              <label for='address2'>Address...</label>
              <input size='15' class='form-control' name='address2' type='text' id='address2' maxlength='50'>
            </div>
          </div>
          <div class="col-sm-6">
            <div class='form-group'>
              <label for='city'>City</label>
              <input size='15' class='form-control' name='city' type='text' id='city' maxlength='50'>
            </div>
          </div>
          <div class="col-sm-6">
            <div class='form-group'>
              <label for='state'>State/Province</label>
              <input size='15' class='form-control' name='state' type='text' id='state' maxlength='50'>
            </div>
          </div>
          <div class="col-sm-6">
            <div class='form-group'>
              <label for='zip'>Postal Code</label>
              <input size='15' class='form-control' name='zip' type='text' id='zip' maxlength='50'>
            </div>
          </div>
          <div class="col-sm-6">
            <label for='country'>Country</label>
            <select name="country" id="country" class="form-control auto-select" autofocus="autofocus" autocorrect="off" autocomplete="off">
              <option value=""></option>
              <?php echo $_smarty_tpl->getSubTemplate ("_countries.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

            </select>
          </div>
          <div class="row">          
          </div>
        </div><!-- #tab3: Address -->

        <div role="tabpanel" class="tab-pane" id="tab4">
          <label for='alert'>NB!</label>
          <textarea rows='1' cols='57' name='alert' id='alert' maxlength='255' class='form-control'></textarea>

          <label for='notes'>Staff notes</label>
          <textarea rows='1' cols='57' name='notes' id='notes' class='form-control'></textarea>

          <label for='message'>Message to guest</label>
          <textarea rows='1' cols='57' name='message' id='message' class='form-control'></textarea>
        </div><!-- #tab4: Notes -->
        
        <div role="tabpanel" class="tab-pane" id="tab5">
          
          <div class="col-sm-6">
            <div class='form-group'>
              <label for='fee_callout'>Callout fee</label>
                <input size='10' name='fee_callout' type='text' id='fee_callout' class='form-control'  onchange='lock_fees();update_overlay_fees()'>
                <input size='4' name='fee_callout_quantity' type='text' value='0.00' id='fee_callout_quantity' class='form-control'  onchange='lock_fees();update_overlay_fees()'>
            </div>
          </div>
          <div class="col-sm-6">
            <div class='form-group'>
              <label for='city'>City</label>
              <input size='15' class='form-control' name='city' type='text' id='city' maxlength='50'>
            </div>
          </div>


          <div class='fieldset_div '><label for='fee_callout_quantity'>Callout fee</label>
          <div class='form-group'>
          </div> 
          <div class='form-group'>
          </div> hours
          </div>
          <div class='fieldset_div '><label for='fee_waiting_quantity'>Waiting fee</label>
          <div class='form-group'>
          <input size='10' name='fee_waiting' type='text' id='fee_waiting' class='form-control'  onchange='lock_fees();update_overlay_fees()'>
          </div> 
          <div class='form-group'>
          <input size='4' name='fee_waiting_quantity' type='text' value='0.00' id='fee_waiting_quantity' class='form-control'  onchange='lock_fees();update_overlay_fees()'>
          </div> hours
          </div>
          <div class='fieldset_div '><label for='fee_cleaning'>Cleaning fee</label>
          <div class='form-group'>
          <input size='10' name='fee_cleaning' type='text' id='fee_cleaning' class='form-control'  onchange='lock_fees();update_overlay_fees()'>
          </div>
          </div>
          <div class='fieldset_div '><label for='fee_local'>Local fee</label>
          <div class='form-group'>
          <input size='10' name='fee_local' type='text' id='fee_local' class='form-control'  onchange='lock_fees();update_overlay_fees()'>
          </div>
          </div>
          <div class='fieldset_div '><label for='fee_booking'>Booking fee</label>
          <div class='form-group'>
          <input size='10' name='fee_booking' type='text' id='fee_booking' class='form-control'  onchange='lock_fees();update_overlay_fees()'>
          </div>
          </div>
          <div class='fieldset_div '><label for='fee_other'>Other fees</label>
          <div class='form-group'>
          <input size='10' name='fee_other' type='text' id='fee_other' class='form-control'  onchange='lock_fees();update_overlay_fees()'>
          </div>
          </div>
          <div class='fieldset_div '><label for='fee_pickup'>Airport pickup</label>
          <div class='form-group'>
          <input size='10' name='fee_pickup' type='text' id='fee_pickup' class='form-control'  onchange='lock_fees();update_overlay_fees()'>
          </div>
          </div>
          <div class='fieldset_div '><label for='fee_locked'>Lock fees?</label>
          <input name='fee_locked' type='hidden'>
          <input name='fee_locked' type='checkbox' value='1' id='fee_locked'>
          </div>

        </div><!-- #tab5: Fees -->
  


      </div>
    </div>
  </div>
  <div class="modal-footer">
    <input type="submit" class="btn btn-primary" value="Save Changes">
    <button type="button" data-dismiss="modal" class="btn">Close</button>
  </div>
  </form>      
</div>

<div id="stack2" class="modal fade" tabindex="-1" data-focus-on="input:first">
  <div class="modal-header">
    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
    <h3>Stack Two</h3>
  </div>
  <div class="modal-body">
    <p>One fine body…</p>
    <p>One fine body…</p>
    <input type="text" data-tabindex="1">
    <input type="text" data-tabindex="2">
    <button class="btn" data-toggle="modal" href="#stack3">Launch modal</button>
  </div>
  <div class="modal-footer">
    <button type="button" data-dismiss="modal" class="btn">Close</button>
    <button type="button" class="btn btn-primary">Ok</button>
  </div>
</div>
       

<!-- Old Modal -->
<div class="modal fade" id="calModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title" id="myModalLabel">Modal title</h4>
      </div>
      <div class="modal-body">
      <form action='/calendar/' method='post' id='cal_dialog_form'><div id='cal_dialog' class='jquery-tabs'>
<ul >
 <li><a href='#cal_dialog_tab_Basic'>Basic</a></li>
 <li><a href='#cal_dialog_tab_Rate'>Rate</a></li>
 <li><a href='#cal_dialog_tab_Fees'>Fees</a></li>
 <li><a href='#cal_dialog_tab_Address'>Address</a></li>
 <li><a href='#cal_dialog_tab_Notes'>Notes</a></li>
</ul>
<div id='cal_dialog_tab_Basic'>

             
<fieldset class='fieldset_left'>
  
  <div class='fieldset_div '>
  
<option value='10' selected='selected'>Unconfirmed</option>
<option value='15'>Proposed</option>
<option value='30'>Reserved</option>
<option value='35'>Blocked</option>
</select></div><div class='fieldset_div '><label for='language'>Language</label><select id='language'  name='language'   >
<option value='en' selected='selected'>English</option>
<option value='nl'>Dutch</option>
<option value='no'>Norwegian</option>
</select></div><div class='fieldset_div '><label for='site_id'>Site</label><select id='site_id'  name='site_id'   >
<option value=''>-- select --</option>
<option value='10'>apartments-for-rent.com</option>
<option value='235'>asapnl.org</option>
<option value='211'>canalapartments.com</option>
<option value='265'>evolutionsports.nl</option>
<option value='263'>hitabrick.com</option>
<option value='216'>jordaanapartmentsamsterdam.com</option>
<option value='231'>kerrygroneng.com</option>
<option value='108'>servicedapartmentamsterdam.com</option>
<option value='264'>strainselector.co</option>
<option value='234'>uhuru.nl</option>
<option value='247'>vpatina.com</option>
<option value='109'>youramsterdamhousing.com</option>
</select></div><div class='fieldset_div '><label for='owner_id'>Owner</label><select id='owner_id'  name='owner_id'   >
<option value=''>-- select --</option>
<option value='1031' selected='selected'>Kjetil Larsen</option>
</select><br></div><div class='fieldset_div '><label for='agent_id'>Agent</label><select id='agent_id'  name='agent_id'   >
<option value=''>-- select --</option>
<option value='2041'>AirBnB</option>
<option value='2010'>Amsterdam Stay</option>
<option value='2028'>Amsterdamby.com</option>
<option value='2018'>Apartmentservice</option>
<option value='2024'>ARC</option>
<option value='2043'>Bethanys</option>
<option value='2054'>BillyPDS</option>
<option value='2031'>Booking.com</option>
<option value='2021'>Bridgestreet</option>
<option value='2033'>Capital Locations</option>
<option value='2017'>Citybaseapartments</option>
<option value='2015'>Easy2Book</option>
<option value='2036'>Eelhouse</option>
<option value='2029'>Halldis</option>
<option value='2011'>Holiday Velvet</option>
<option value='2019'>Holidaylettings</option>
<option value='2027'>Hotels.nl</option>
<option value='2050'>Housetrip</option>
<option value='2037'>Htel</option>
<option value='2049'>IRM</option>
<option value='2034'>Maak It</option>
<option value='2030'>Oakwood UK</option>
<option value='2023'>Oakwood USA</option>
<option value='2020'>Primacy</option>
<option value='2016'>Saco Apartments</option>
<option value='2014'>Scentic Tours</option>
<option value='2055'>Settle Services</option>
<option value='2052'>Silverdoor</option>
<option value='2042'>test sicco</option>
<option value='2013'>The MI Group NY</option>
<option value='2022'>Thomas Zwart</option>
<option value='2044'>Wimdu</option>
<option value='2025'>Xpat rentals</option>
</select><br></div><div class='fieldset_div '><label for='org_id'>Company</label><select id='org_id'  name='org_id'   >
<option value=''>-- select --</option>
<option value='3520'> Levador Viaggi di Guicos Srl</option>
<option value='2026'>180 Amsterdam BV</option>
<option value='2050'>Accenture</option>
<option value='2012'>Accenture</option>
<option value='2051'>Aires</option>
<option value='3581'>AIRes</option>
<option value='2011'>Akqa</option>
<option value='3504'>Altair - Footlocker</option>
<option value='3526'>Andaz Amsterdam</option>
<option value='2013'>Basf</option>
<option value='3546'>Bass Films, LLC</option>
<option value='2044'>Better Place</option>
<option value='3561'>BillyPDS</option>
<option value='2047'>Bridgestreet Worldwide</option>
<option value='3564'>Bristol Global Mobility</option>
<option value='3501'>Cartus Corporation</option>
<option value='2014'>Cisco</option>
<option value='2017'>Clifford Chance</option>
<option value='3536'>Creative Industry Amsterdam</option>
<option value='3519'>DEAKIN UNIVERSITY</option>
<option value='3508'>Deep Sea Metro Holland BV</option>
<option value='2022'>Desato</option>
<option value='2018'>Diageo Brands BV</option>
<option value='3579'>Diageo Brands BV / Ivanka Jansen</option>
<option value='3567'>Diageo C/O Bristol Global Mobility</option>
<option value='3569'>Diageo C/O Brookfield Global Relocation Services</option>
<option value='3576'>eBay C/O Silverdoor</option>
<option value='2006'>Effectory</option>
<option value='2058'>Ekat Textile and trade Co.</option>
<option value='2025'>Emerson</option>
<option value='3524'>Eni trading & shipping B.V.</option>
<option value='2003'>Ernst & Young</option>
<option value='3551'>Etihad Airways</option>
<option value='3560'>Etihad Airways (NL)</option>
<option value='3557'>Footlocker</option>
<option value='2015'>General Electrics</option>
<option value='3552'>Gree Inc</option>
<option value='2042'>Heineken</option>
<option value='3511'>Housetrip</option>
<option value='3502'>HP Polska NIP: 527-02-05-128</option>
<option value='3521'>International Vision Centers</option>
<option value='2059'>Intralot SA</option>
<option value='3584'>Irdeto BV</option>
<option value='3527'>IRM Limited</option>
<option value='2049'>Jeffrey Grauer</option>
<option value='3578'>Juniper Networks International BV</option>
<option value='2028'>KPMG Meijburg Expatriate Servi</option>
<option value='3525'>Laureate</option>
<option value='3559'>Liberty Global B.V</option>
<option value='2057'>McGregors</option>
<option value='2019'>Mexx</option>
<option value='2021'>Molecular</option>
<option value='2060'>Morais Leitão, Galvão Teles,</option>
<option value='151'>MyCorp</option>
<option value='3545'>NetCracker Technology</option>
<option value='2004'>Nike (Crown Relo)</option>
<option value='3575'>NIKE European Operations NL BV</option>
<option value='0'>None</option>
<option value='3505'>Oakwood International, LCC</option>
<option value='2046'>Orican Holdings</option>
<option value='2048'>Paragon</option>
<option value='3583'>Patagonia Europe Cooperatief UA</option>
<option value='3548'>Pepper and Salt</option>
<option value='3573'>Plantronics Inc</option>
<option value='3509'>Pure Dino BV</option>
<option value='3577'>Randstad Holding NV</option>
<option value='3544'>Reckitt Banckiser Netherlands BV</option>
<option value='3566'>Relocaid</option>
<option value='2062'>RightNow</option>
<option value='3568'>Roomlr BV</option>
<option value='3538'>Royal Bank of Scotland</option>
<option value='2052'>Saco Apartments</option>
<option value='2023'>SAP</option>
<option value='3574'>Settle Service BV</option>
<option value='3572'>Seyfarth Shaw LLP</option>
<option value='2020'>Shell</option>
<option value='3522'>Shopmill BV</option>
<option value='3506'>SID LEE</option>
<option value='3541'>Silverdoor Ltd</option>
<option value='2056'>Sirva Relocation</option>
<option value='3542'>Square Box Media Solutions</option>
<option value='2054'>Starbucks Coffee EMEA bv</option>
<option value='2055'>Starbucks Manufact. EMEA BV</option>
<option value='2045'>SuccessFactors</option>
<option value='3503'>Talisman Int. Holdings BV</option>
<option value='3507'>Tesa</option>
<option value='3565'>TEVA Pharmaceuticals Europe BV</option>
<option value='2061'>The MI Group</option>
<option value='2001'>The MI Group</option>
<option value='2032'>Thomson Reuters</option>
<option value='3528'>Top Victory Investments Limited</option>
<option value='3571'>TOP VICTORY INVESTMENTS LIMITED</option>
<option value='3582'>TVN Real Estate BV</option>
<option value='2002'>Under Armour</option>
<option value='3558'>Weichert Relocation UK Ltd</option>
<option value='3563'>Weichert Relocation UK Ltd</option>
<option value='152'>Wieden + Kennedy</option>
<option value='2005'>WRRI UK</option>
</select>

<a title='Add org' href='#'>
 <img src='/images/icons/add_small.png' alt='Add org'></a></div>

<div class='fieldset_div hidden' id="org_contact">
<label for='contact_id'>Contact</label><select id='contact_id'  name='contact_id'   >
<option value=''>-- select --</option>
</select> <input name='invoice_contact' type='hidden'><input name='invoice_contact' type='checkbox' value='1' id='invoice_contact'>Invoice contact</div>
 </fieldset>

<br>



<div id='cal_dialog_tab_Rate'>
 <fieldset class='fieldset_left_wide rate_fieldset'>  
 </fieldset>
</div>


<div id='cal_dialog_tab_Fees'>
 <fieldset class='fieldset_left_wide'>
  
 </fieldset>
</div>
<div id='cal_dialog_tab_Address'>           
 <fieldset class='fieldset_top'>
  
  
<div class='fieldset_div '><label for='address1'>Address</label>
<div class='form-group'>
<input size='15' class='form-control' name='address1' type='text' id='address1' maxlength='50'></div></div>
<div class='fieldset_div '><label for='address2'>Address...</label>
<div class='form-group'>
<input size='15' class='form-control' name='address2' type='text' id='address2' maxlength='50'></div></div>
<div class='fieldset_div '><label for='city'>City</label>
<div class='form-group'>
<input size='15' class='form-control' name='city' type='text' id='city' maxlength='50'></div></div>
<div class='fieldset_div '><label for='state'>State/Province</label>
<div class='form-group'>
<input size='15' class='form-control' name='state' type='text' id='state' maxlength='50'></div></div>
<div class='fieldset_div '><label for='zip'>Postal Code</label>
<div class='form-group'>
<input size='15' class='form-control' name='zip' type='text' id='zip' maxlength='50'></div></div>
<div class='fieldset_div '><label for='country'>Country</label>
  <select name="country" id="country" class="auto-select" autofocus="autofocus" autocorrect="off" autocomplete="off">
   <option value=""></option>
   

  </select>                                 
</div>
 </fieldset>
</div><div id='cal_dialog_tab_Notes'>
 <fieldset class='fieldset_top'>
  
 </fieldset>
</div></div></form>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
        <button type="button" class="btn btn-primary">Save changes</button>
      </div>
    </div>
  </div>
</div>

<?php }} ?>
