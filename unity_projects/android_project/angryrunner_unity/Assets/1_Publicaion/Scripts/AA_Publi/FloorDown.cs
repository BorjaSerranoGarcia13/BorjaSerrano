using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FloorDown : MonoBehaviour
{
    bool go_down;
    bool start_moving;
    float dir;
    // Start is called before the first frame update
    void Start()
    {
      go_down = false;
      start_moving = false;
      dir = 1;
    }

    // Update is called once per frame
    void Update()
    {
      if (go_down)
      {
        transform.position = new Vector3(transform.position.x, transform.position.y - 2.0f * Time.deltaTime, transform.position.z);
      }

      if (start_moving)
      {
        transform.position = new Vector3(transform.position.x, transform.position.y - 2.0f * Time.deltaTime * dir, transform.position.z);
        dir *= -1;
      }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {

          StartCoroutine(WaitForMove(0.2f));
        }
    }

    IEnumerator WaitForMove(float time)
    {
      start_moving = true;
      yield return new WaitForSeconds(time);
      start_moving = false;
      go_down = true;
    }
}
