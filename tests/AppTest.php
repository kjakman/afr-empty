<?php
 
use kjakman\AFR\Application;
 
class AppTest extends PHPUnit_Framework_TestCase {
 
  public function testApp()
  {
    $app = new Application;
    $this->assertTrue($app->());
  }
 
}