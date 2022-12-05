using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FallFloor : MonoBehaviour
{
    public bool gravityFloor = true;
    bool gravity_down = false;
    int count = 0;

    Vector3 reset_pos;
    // Start is called before the first frame update
    void Start()
    {
        gravity_down = false;
        reset_pos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
      if (gravity_down)
      {
        if (count < 3000)
        {
          transform.position -= new Vector3(0, 4.0f * Time.deltaTime, 0);
          count++;
        }
        else
        {
          transform.position = reset_pos;
          gravity_down = false;
          count = 0;
        }
      }

    }

    private void OnTriggerExit(Collider other)
    {
      if (gravityFloor)
      {
        gravity_down = true;
      }
    }


}
