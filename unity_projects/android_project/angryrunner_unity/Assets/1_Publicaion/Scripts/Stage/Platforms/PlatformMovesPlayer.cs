using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformMovesPlayer : MonoBehaviour
{
  /*
    CharacterController player;
    PJ_Movement script;

    Vector3 actualPosition;
    Vector3 lastPosition;
    Vector3 f;

    bool movePlayer;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
        script = GameObject.Find("Player").GetComponent<PJ_Movement>();

        actualPosition = transform.position;
        lastPosition = actualPosition;
        movePlayer = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (movePlayer)
        {
            actualPosition = transform.position;
            f = actualPosition - lastPosition;

            if (player.isGrounded)
            {
                player.Move(f);
            }

            lastPosition = actualPosition;
        }
        //if (player.isGrounded) Debug.Log("suelo");
        //else Debug.Log("vuelo");

    }

    private void OnTriggerStay(Collider other)
    {
        if (other.tag == "Player")
        {
            player.Move(Vector3.zero);
            movePlayer = true;
            script.jumped = false;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        movePlayer = false;
        script.jumped = true;
    }*/
}
