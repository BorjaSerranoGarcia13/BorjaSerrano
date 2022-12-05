using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PJ_Movement : MonoBehaviour
{
    CharacterController player;

    // MOVEMENT
    private Vector3 playerInput;
    public Vector3 movePlayer; 
    private float horizontalMove;
    private float verticalMove;
        // SPEED
    public float playerSpeed;
        // GRAVITY
    public float gravity;
    public float fallVelocity;
        // JUMP
    public float jumpForce;
        // SLIDE
    private Vector3 hitNormal;
    public bool isOnSlope = false;
    public float slideVelocity;
    public float slopeForceDown;

    // CAMERA
    public Camera mainCamera;
    private Vector3 camForward;
    private Vector3 camRight;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
    }

    // Update is called once per frame
    void Update()
    {
        horizontalMove = Input.GetAxis("Horizontal");
        verticalMove = Input.GetAxis("Vertical");

        playerInput = new Vector3(horizontalMove, 0, verticalMove);
        playerInput = Vector3.ClampMagnitude(playerInput, 1);

        CamDirection();

        movePlayer = playerInput.x * camRight + playerInput.z * camForward;

        movePlayer = movePlayer * playerSpeed;

        player.transform.LookAt(player.transform.position + movePlayer);

        SetGravity();

        PlayerJump();

        player.Move(movePlayer * Time.deltaTime);
    }

    private void CamDirection()
    {
        camForward = mainCamera.transform.forward;
        camRight = mainCamera.transform.right;

        camForward.y = 0;
        camRight.y = 0;

        camForward = camForward.normalized;
        camRight = camRight.normalized;
    }

    public void PlayerJump()
    {
        if (player.isGrounded && Input.GetButtonDown("Jump") && jumpForce > 0)
        {
            fallVelocity = jumpForce;
            movePlayer.y = fallVelocity;// si ponemos *deltaTime conseguimos impulso
        }
    }

    void SetGravity()
    {
        if (player.isGrounded) fallVelocity = -gravity * Time.deltaTime;
        else  fallVelocity -= gravity * Time.deltaTime;
        
        movePlayer.y = fallVelocity;

        SlideDown();
    }

    public void SlideDown()
    {
        isOnSlope = Vector3.Angle(Vector3.up, hitNormal) >= player.slopeLimit + 15;

        if (isOnSlope == true)
        {
            movePlayer.x += ((1f - hitNormal.y) * hitNormal.x ) * slideVelocity;
            movePlayer.z += ((1f - hitNormal.y) * hitNormal.z ) * slideVelocity;
           
            //movePlayer.y += slopeForceDown;
        }
    }

    private void OnControllerColliderHit(ControllerColliderHit hit)
    {
        hitNormal = hit.normal;
    }
}
