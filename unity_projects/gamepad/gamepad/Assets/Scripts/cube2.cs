using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem.PlayerInput;

public class cube2 : MonoBehaviour
{
    Vector2 movement;
    public float speed = 1f;
    public float speedBall = 0.5f;
    public float speedNoBall = 1.0f;

    Vector2 shot;
    public float forceShot = 0.0f;
    Vector3 saveForceShot;
    bool activateShot;

    GameObject ball;

    scoreCounter script;

    public int nPlayer;

    ball script2;

    Vector3 direction;

    void Start()
    {
        forceShot = 0.0f;
        saveForceShot = Vector3.zero;

        script = GameObject.Find("ScoreManager").GetComponent<scoreCounter>();

        script2 = GameObject.Find("Ball").GetComponent<ball>();

        ball = GameObject.Find("Ball");

        activateShot = false;

        direction = Vector3.zero;
    }

    // Update is called once per frame
    void Update()
    {

      if (script.movActive)
      {
        Move();

        if (nPlayer == script2.playerBall)
        {
          transform.GetChild(0).transform.GetComponent<Collider>().isTrigger = false;
          ball.transform.position = transform.GetChild(0).transform.position;
          if (shot != Vector2.zero)
          {
            Shoot();
            activateShot = true;
          }
          else
          {
            if (activateShot)
            {
              ball.transform.parent = null;
              script2.playerBall = 0;
              ball.GetComponent<Rigidbody>().AddForce(saveForceShot, ForceMode.Impulse);
              forceShot = 0.0f;
              activateShot = false;
            }
          }
          speed = speedBall;
        }
        else
        {
          speed = speedNoBall;
          transform.GetChild(0).transform.GetComponent<Collider>().isTrigger = true;
        }
      }
      else
      {
        GetComponent<Rigidbody>().velocity = Vector3.zero;
        GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
      }
    }

    void Move()
    {
      Vector3 m = new Vector3(movement.x, 0, movement.y) * speed;
      gameObject.GetComponent<Rigidbody>().velocity = m;
    }

    void OnMove(InputValue value)
    {
      movement = value.Get<Vector2>();
      direction = new Vector3(-movement.y, 0.0f, movement.x);
      if(direction.sqrMagnitude > 0.1f)
      {
        transform.LookAt(transform.position + direction);
      }
    }

    void Shoot()
    {
      Vector3 s = new Vector3(shot.x, 0, shot.y) * Time.deltaTime;
      //if (forceShot > 200.0f) { forceShot += 20.0f; }
      forceShot = 1000.0f;
      saveForceShot = s * forceShot;
    }

    void OnShoot(InputValue value)
    {
      shot = value.Get<Vector2>();

    }

}
