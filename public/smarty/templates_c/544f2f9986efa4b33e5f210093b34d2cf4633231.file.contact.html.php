<?php /* Smarty version Smarty-3.1.20, created on 2015-06-01 07:48:29
         compiled from "/web/comps/php/apt/smarty/templates/contact.html" */ ?>
<?php /*%%SmartyHeaderCode:2029381904556c0e4dd681a4-87887082%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '544f2f9986efa4b33e5f210093b34d2cf4633231' => 
    array (
      0 => '/web/comps/php/apt/smarty/templates/contact.html',
      1 => 1433144909,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '2029381904556c0e4dd681a4-87887082',
  'function' => 
  array (
  ),
  'has_nocache_code' => false,
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_556c0e4dd95a96_26967724',
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_556c0e4dd95a96_26967724')) {function content_556c0e4dd95a96_26967724($_smarty_tpl) {?>
        <!-- Content Row -->
        <div class="row">
            <!-- Map Column -->
            <div class="col-md-8">
                <!-- Embedded Google Map -->
                <iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d155796.87600174773!2d4.910393998283322!3d52.40076425853433!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x47c609cee88a6797%3A0xd279889db3dbb290!2sKorte+Prinsengracht+48%2C+1013+GT+Amsterdam%2C+Nederland!5e0!3m2!1snl!2sus!4v1409392778212" width="600" height="450" frameborder="0" style="border:0"></iframe>
            </div>
            <!-- Contact Details Column -->
            <div class="col-md-4">
                <h3>Contact Details</h3>
                <p>Korte Prisengracht 48H<br>1013 GT Amsterdam, The Netherlands<br></p>
                <p><i class="fa fa-phone"></i> 
                    <abbr title="Phone">P</abbr>: +31 642200934</p>
                <p><i class="fa fa-envelope-o"></i> 
                    <abbr title="Email">E</abbr>: <a href="mailto:">info@vpatina.com</a>
                </p>
                <p><i class="fa fa-clock-o"></i> 
                    <abbr title="Hours">H</abbr>: Monday - Friday: 9:00 AM to 5:00 PM</p>
                <ul class="list-unstyled list-inline list-social-icons">
                    <li>
                        <a href="#"><i class="fa fa-facebook-square fa-2x"></i></a>
                    </li>
                    <li>
                        <a href="#"><i class="fa fa-linkedin-square fa-2x"></i></a>
                    </li>
                    <li>
                        <a href="#"><i class="fa fa-twitter-square fa-2x"></i></a>
                    </li>
                    <li>
                        <a href="#"><i class="fa fa-google-plus-square fa-2x"></i></a>
                    </li>
                </ul>
            </div>
        </div>
        <!-- /.row -->

        <!-- Contact Form -->
        <!-- In order to set the email address and subject line for the contact form go to the bin/contact_me.php file. -->
        <div class="row">
            <div class="col-md-8">
                <h3>Send us a Message</h3>
                <form name="sentMessage" id="contactForm" novalidate>
                    <div class="control-group form-group">
                        <div class="controls">
                            <label>Full Name:</label>
                            <input type="text" class="form-control" id="name" required data-validation-required-message="Please enter your name.">
                            <p class="help-block"></p>
                        </div>
                    </div>
                    <div class="control-group form-group">
                        <div class="controls">
                            <label>Phone Number:</label>
                            <input type="tel" class="form-control" id="phone"><!-- required data-validation-required-message="Please enter your phone number."-->
                        </div>
                    </div>
                    <div class="control-group form-group">
                        <div class="controls">
                            <label>Email Address:</label>
                            <input type="email" class="form-control" id="email" required data-validation-required-message="Please enter your email address.">
                        </div>
                    </div>
                    <div class="control-group form-group">
                        <div class="controls">
                            <label>Message:</label>
                            <textarea rows="10" cols="100" class="form-control" id="message" required data-validation-required-message="Please enter your message" maxlength="999" style="resize:none"></textarea>
                        </div>
                    </div>
                    <div id="success"></div>
                    <!-- For success/fail messages -->
                    <button type="submit" class="btn btn-primary">Send Message</button>
                </form>
            </div>

        </div>
        <!-- /.row -->
        <script src="/bower/jqBootstrapValidation/dist/jqBootstrapValidation-1.3.7.min.js"></script>
        <script src="/afr/js/contact_me.js"></script>


<?php }} ?>
