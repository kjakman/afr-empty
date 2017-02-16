<?php
namespace AFR\Controller;

class Test extends BaseController {
	protected function index() {
		$scope = new \stdClass;
		$scope->primus = 'sucks';
		$this->scope = $scope;
		return $scope;
	}	
	protected function view($obj_id) {
		$scope = new \stdClass;
		$scope->params = ['id' => 1];
		$this->scope = $scope;
		return $scope;
	}	
	protected function edit($obj_id, $subview='') {
		$scope = new \stdClass;
		$scope->params = ['id' => 1, 'subview' => 0];
		$this->scope = $scope;
		return $scope;
	}	
	protected function details($obj_id, $subview) {
		$scope = new \stdClass;
		$scope->params = ['id' => 1, 'subview' => 1];
		$this->scope = $scope;
		return $scope;
	}	
	protected function browse($subview) {
		$scope = new \stdClass;
		$scope->params = ['subview' => 1];
		$this->scope = $scope;
		return $scope;
	}	
}

