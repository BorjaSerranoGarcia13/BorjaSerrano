using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goal : MonoBehaviour
{
    // Start is called before the first frame update
    [SerializeField]
    private string level_name;
    private GameObject ruler;
    private GameInstance game_inst; 
    private void Start()
    {
        ruler = GameObject.Find("Ruler");
        game_inst = ruler.GetComponent<GameInstance>();
    }
    private void OnTriggerEnter(Collider other)
    {
        game_inst.ChangeScene(level_name);
    }

}
