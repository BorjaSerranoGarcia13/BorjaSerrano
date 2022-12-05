using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rock : MonoBehaviour
{

    private int direction; // 0 go down 1 go up
    private float speed;
    private float direction_count;

    void Start()
    {
        direction = 0;
        speed = 10.0f;
        direction_count = 0;
    }


    void Update()
    {
        Speed_Rock();


    }

    void Speed_Rock()
    {
        if (direction == 0) speed = 10.0f;
        else speed = 6.0f;
    }

    void Movement_Rock()
    {
        if (direction_count >=300)
        {
            if (direction == 0)
            {
                transform.position = new Vector3(transform.position.x , transform.position.y - speed * Time.deltaTime, transform.position.z);
            }else
            {
                transform.position = new Vector3(transform.position.x, transform.position.y + speed * Time.deltaTime, transform.position.z);
            }
     
        }
        

        direction_count += 1;
        if (direction_count > 500) direction_count = 0;
    }
}
