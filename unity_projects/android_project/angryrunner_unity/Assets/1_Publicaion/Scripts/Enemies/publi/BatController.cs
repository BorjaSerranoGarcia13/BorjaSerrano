using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BatController : MonoBehaviour
{
    public GameObject bat_;
    public GameObject follow_;
    public float fireRate_;
    private float cooldown_;
    GameObject player;

    private float randomY;

    Bats script;

    [SerializeField]
    //float range[2];
    // Start is called before the first frame update
    void Start()
    {
      player = GameObject.Find("Player").GetComponent<GameObject>();
      cooldown_ = fireRate_ * 0.99f;
    }

    // Update is called once per frame
    void Update()
    {
      cooldown_ += Time.deltaTime;
      randomY = Random.Range(0,2);

      if (cooldown_ >= fireRate_)
      {
        Instantiate( bat_,transform.position, transform.rotation);
        /*script = bat_.GetComponent<Bats>();
        if (follow_ != null) script.follow = follow_;
        else script.follow = player;*/
        cooldown_ = 0.0f;
      }
    }


}
