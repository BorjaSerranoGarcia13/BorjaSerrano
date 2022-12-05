using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoorEnemyGenerator : MonoBehaviour
{
    
    public GameObject enemy_prefab;
    
    public float generate_time;
    bool open=true;
    GameObject player;
    
   public float aggro_range = 0;
    float distance;
    DoorOpen opener;
    bool generation = true;
    
   public Transform generation_position;
    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        opener = gameObject.GetComponent<DoorOpen>();

    }

    // Update is called once per frame
    void Update()
    {
        distance = Vector3.Distance(transform.position,player.transform.position);
        if (distance < aggro_range)
        {
            if (open)
            {
                opener.Open();
                if (generation) { generation = false; StartCoroutine(Generator()); }
            }
            else
            {
                opener.Close();
                if (!generation) { generation = true; StartCoroutine(Generator()); }
            }
        }
        else opener.Stop();
    }
    IEnumerator Generator()
    {

        yield return new WaitForSeconds(generate_time);
        if(!generation)Instantiate(enemy_prefab, generation_position.position, generation_position.rotation);
        if (open) open = false;
        else open = true;
    }

}
