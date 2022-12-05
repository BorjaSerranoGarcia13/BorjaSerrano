using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformMovesPlayer : MonoBehaviour
{
    GameObject player;
    movement2 script;

    Vector3 actualPosition;
    Vector3 lastPosition;
    Vector3 f;

    bool movePlayer;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.FindWithTag("Player");
        script = player.GetComponent<movement2>();

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

            if (script.ground)
            {
              //player.transform.position += f;
            }

            lastPosition = actualPosition;
        }

    }

    private void OnTriggerStay(Collider other)
    {
        if (other.tag == "Player")
        {
          movePlayer = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
      movePlayer = false;
    }

}
