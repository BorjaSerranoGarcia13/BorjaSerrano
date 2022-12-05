using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoorOpen : MonoBehaviour
{
    [SerializeField]
    float door_speed=30;
    private Transform[] doors;
    bool open_door;
    bool close_door;
    // Start is called before the first frame update
    void Start()
    {
        doors = GetComponentsInChildren<Transform>();
       
    }
    private void Update()
    {
        if (open_door) OpenDoor();
        if (close_door) CloseDoor();


    }
    public void Open() {
        open_door = true;
        close_door = false;
    }
    public void Close() {
        open_door = false;
        close_door = true;
    }
    public void Stop()
    {
        open_door = false;
        close_door = false;
    }

    void OpenDoor()
    {
        
            doors[1].transform.Rotate(0, Time.deltaTime * -door_speed, 0);
            doors[3].transform.Rotate(0, Time.deltaTime * door_speed, 0);
        
    }

     void CloseDoor()
    {
        doors[1].transform.Rotate(0, Time.deltaTime * door_speed, 0);
        doors[3].transform.Rotate(0, Time.deltaTime * -door_speed, 0);
    }

}
