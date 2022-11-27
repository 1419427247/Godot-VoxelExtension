extends CharacterBody3D

class_name GDController

enum Person{
	FIRST,
	THIRD,
}

@onready var collision_shape : CollisionShape3D= $CollisionShape
@onready var sprint_arm : SpringArm3D = $SpringArm3d
@onready var camera : Camera3D = $SpringArm3d/Camera
@onready var ray_cast : RayCast3D = $SpringArm3d/Camera/RayCast
@onready var input_panel : Control = $InputPanel

@export_enum("First person","Thrid person") 
var type : int = Person.FIRST

@export
var disable : bool = false : 
	set(value):
		if(value == true):
			Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
		else:
			Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
		disable = value
	get:
		return disable

@export
var input : bool = true

@export var gravity : float = -20
@export var flying : bool = false
@export var ghost : bool = false

@export_range(0,1)
var move_interpolation : float = 0.25
@export var move_speed : float = 100

@export var jumping_duration : float = 0.07
@export var jumping_force : float = 75

@export var maximum_falling_speed : float = 32

@export var mouse_sensitivity_x : float = 0.15
@export var mouse_sensitivity_y : float = 0.15
@export_group("FirstPerson")

@export var camera_angle_limit_max: float = 90
@export var camera_angle_limit_min: float = -90

@export_group("ThirdPerson")
@export var camera_distance: float = 3

var _mouse_direction : Vector3 = Vector3.ZERO
func _first_person_update() -> void:
	sprint_arm.spring_length = 0
	rotate_y(deg_to_rad(_mouse_direction.y))
	sprint_arm.rotate_x(deg_to_rad(_mouse_direction.x))
	if(rad_to_deg(sprint_arm.rotation.x) > camera_angle_limit_max):
		sprint_arm.rotation.x = deg_to_rad(camera_angle_limit_max)
	if(rad_to_deg(sprint_arm.rotation.x) < camera_angle_limit_min):
		sprint_arm.rotation.x = deg_to_rad(camera_angle_limit_min)
	_mouse_direction = Vector3.ZERO

func _third_person_update() -> void:
	sprint_arm.spring_length = camera_distance
	sprint_arm.rotate_x(deg_to_rad(_mouse_direction.x))
	rotate_y(deg_to_rad(_mouse_direction.y))
	_mouse_direction = Vector3.ZERO

func _process(delta: float) -> void:
	if(input == true):
		Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
	else:
		Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
	match type:
		Person.FIRST:
			_first_person_update()
		Person.THIRD:
			_third_person_update()
	
var _is_jumping : bool = false
var _jumping_time : float = 0
func _physics_process(delta: float) -> void:
	collision_shape.disabled = ghost
	if(disable == true):
		return
	if(flying == true):
		if(Input.is_action_pressed("key_forward") and input == true):
			velocity -= global_transform.basis.z * move_speed * delta;
		if(Input.is_action_pressed("key_backward") and input == true):
			velocity += global_transform.basis.z * move_speed * delta;
		if(Input.is_action_pressed("key_left") and input == true):
			velocity -= global_transform.basis.x * move_speed * delta;
		if(Input.is_action_pressed("key_right") and input == true):
			velocity += global_transform.basis.x * move_speed * delta;
		if(Input.is_action_pressed("key_space") and input == true):
			velocity += global_transform.basis.y * move_speed * delta;
		if(Input.is_action_pressed("key_ctrl") and input == true):
			velocity -= global_transform.basis.y * move_speed * delta;
		velocity = velocity.lerp(Vector3.ZERO,move_interpolation)
	else:
		if(is_on_floor() == true):
			if(Input.is_action_pressed("key_forward") and input == true):
				velocity -= transform.basis.z * move_speed * delta
			if(Input.is_action_pressed("key_backward") and input == true):
				velocity += transform.basis.z * move_speed * delta
			if(Input.is_action_pressed("key_left") and input == true):
				velocity -= transform.basis.x * move_speed * delta
			if(Input.is_action_pressed("key_right") and input == true):
				velocity += transform.basis.x * move_speed * delta
			if(_jumping_time != 0):
				velocity = velocity * 0.2
				_jumping_time = 0
			if(Input.is_action_just_pressed("key_space") and input == true):
				_is_jumping = true
			velocity = Vector3(0,velocity.y,0) + Vector3(velocity.x,0,velocity.z).lerp(Vector3.ZERO,move_interpolation)
		else:
			if(Input.is_action_pressed("key_forward") and input == true):
				velocity -= transform.basis.z * move_speed * delta * 0.1
			if(Input.is_action_pressed("key_backward") and input == true):
				velocity += transform.basis.z * move_speed * delta * 0.1
			if(Input.is_action_pressed("key_left") and input == true):
				velocity -= transform.basis.x * move_speed * delta * 0.1
			if(Input.is_action_pressed("key_right") and input == true):
				velocity += transform.basis.x * move_speed * delta * 0.1
			velocity = Vector3(0,velocity.y,0) + Vector3(velocity.x,0,velocity.z).lerp(Vector3.ZERO,move_interpolation * 0.2)
		if(_is_jumping == true):
			_jumping_time += delta
			velocity += global_transform.basis.y * jumping_force * delta * (1 / _jumping_time * _jumping_time);
			if(_jumping_time > jumping_duration):
				_is_jumping = false
		else:
			velocity += global_transform.basis.y * gravity * delta;
	move_and_slide()

func _input(event):	
	if event is InputEventKey:
		if(event.is_action_released("key_alt") and input == true):
			input = false
	if(disable == true or input == false):
		return
	if event is InputEventMouseMotion:
		_mouse_direction = Vector3(-event.relative.y * mouse_sensitivity_y,-event.relative.x * mouse_sensitivity_x,0)

func _on_input_panel_gui_input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		input = true
