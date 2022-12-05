using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PJ_Movement : MonoBehaviour
{
    CharacterController player;
    // MOVEMENT
    private Vector3 playerInput;
    public Vector3 movePlayer;
    private float horizontalMove;
    private float verticalMove;
    private Vector3 mirror;

        // SPEED
    public float playerSpeed;
        // GRAVITY
    public float gravity;
    public float fallVelocity;
        // JUMP
    public float jumpForce;
    public bool jumped = false;

    // CAMERA
    private Camera mainCamera;
    private Vector3 camForward;
    private Vector3 camRight;

    // ANIMATION
    private Animator animator;

     ControlAndroid script;

     Joystick joystick;

     static int n_level;
     int n_stars;

     public AudioSource jump;

    // Start is called before the first frame update
    void Start()
    {
        n_level = SceneManager.GetActiveScene().buildIndex;
        if (Levels.levels[n_level - 1].stars < n_stars) Levels.levels[n_level - 1].stars = n_stars;

        mainCamera = GameObject.FindGameObjectWithTag("MainCamera").GetComponent<Camera>();
        player = GameObject.FindWithTag("Player").GetComponent<CharacterController>();
        mirror = new Vector3(0.0f, 180.0f, 0.0f);

        animator = GetComponent<Animator>();

        script = GameObject.Find("ControlAndroid").GetComponent<ControlAndroid>();

        joystick = GameObject.Find("Joystick").GetComponent<Joystick>();
        script.jump = false;
    }

    // Update is called once per frame
    void Update()
    {

        horizontalMove = joystick.Horizontal;


        playerInput = new Vector3(horizontalMove, 0, 0);
        playerInput = Vector3.ClampMagnitude(playerInput, 1);

        CamDirection();

        movePlayer = playerInput.x * camRight + playerInput.z * camForward;

        movePlayer = movePlayer * playerSpeed;

        if (horizontalMove < 0 ) {
            transform.eulerAngles = mirror;
        }
        else if (horizontalMove > 0) {
            transform.eulerAngles = Vector3.zero;
        }

        SetGravity();

        if (horizontalMove != 0 && animator.GetBool("jumping") == false)
        {
          animator.SetBool("running", true);
        }
        else if (horizontalMove == 0)
        {
          animator.SetBool("running", false);
        }
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
      if (player.isGrounded)
      {
        animator.SetBool("jumping", false);
        animator.SetBool("running", true);
        jumped = false;
      }


      if (Input.GetButtonDown("Jump") || script.jump)
      {
        if (!jumped && jumpForce > 0)
        {
            jump.Play();
            jumped = true;
            fallVelocity = jumpForce;
            movePlayer.y = fallVelocity;// si ponemos *deltaTime conseguimos impulso
            animator.SetBool("running", false);
            animator.SetBool("jumping", true);
            script.jump = false;
        }
      }
    }

    void SetGravity()
    {
        if (player.isGrounded) fallVelocity = -gravity * Time.deltaTime;
        else  fallVelocity -= gravity * Time.deltaTime;

        movePlayer.y = fallVelocity;
    }

}
