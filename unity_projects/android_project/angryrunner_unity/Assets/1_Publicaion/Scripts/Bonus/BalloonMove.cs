using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BalloonMove : MonoBehaviour
{
    
    float speed;
    Vector3 movement;
    static int pos;
    Vector3 mouse_position;

    void Start()
    {
        int posX = Random.Range(0,8);
        
        if (pos == posX) posX += 2;
        if (posX == 8) posX = 0;
        else if (pos == 9) posX = 1;

        switch(posX)
        {
            case 0:  transform.position = new Vector3(-2.5f, -8.0f, 0.0f);
                   break;
            case 1:  transform.position = new Vector3(-0.07f, -8.0f, 0.0f);
                   break;
            case 2:  transform.position = new Vector3(0.0f, -8.0f, 0.0f);
                   break;
            case 3:  transform.position = new Vector3(4.36f, -8.0f, 0.0f);
                   break;
            case 4:  transform.position = new Vector3(6.7f, -8.0f, 0.0f);
                   break;
            case 5:  transform.position = new Vector3(8.9f, -8.0f, 0.0f);
                   break;
            case 6:  transform.position = new Vector3(11.1f, -8.0f, 0.0f);
                   break;
            case 7:  transform.position = new Vector3(13f, -8.0f, 0.0f);
                   break;
                  
        }
        pos = posX;
        transform.position = new Vector3(Random.Range(-2.5f, 14f), -8.0f, 0.0f);
        int scale = Random.Range(0,3);
        float x, y, z;
        switch(scale)
        {
            case 0: x = 1; y = 1; z = 1;
                   transform.localScale = new Vector3(x, y, z);
                   speed = Random.Range(2.0f,3.0f);
                   break;
           case 1: x = 0.7f; y = 0.7f; z = 0.7f;
                   transform.localScale = new Vector3(x, y, z);
                   speed = Random.Range(3.0f,4.0f);
                   break;
           case 2: x = 0.4f; y = 0.4f; z = 0.4f; 
                   transform.localScale = new Vector3(x, y, z);
                   speed = Random.Range(4.0f,5.0f);
                   break;
       }
    }

    // Update is called once per frame
    void Update()
    {
       movement = new Vector3(0.0f, 1.0f, 0.0f);
       transform.position += movement * speed * Time.deltaTime;
       if (transform.position.y > 9) Destroy(gameObject);
       mouse_position = new Vector3(Input.mousePosition.x, Input.mousePosition.y, 0.0f);
    }

    void OnMouseDown()
    {
       BalloonController.total_score += 10;
       Destroy(gameObject);
       //if (transform.position == mouse_position) Debug.Log("globo");
    }
}
