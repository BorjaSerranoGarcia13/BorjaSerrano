using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using UnityEngine.Monetization;
using UnityEngine.Advertisements;


public class Ads : MonoBehaviour, IUnityAdsListener
{
  private string playstoreID = "3593066";
  private string appstoreID = "3593067";

  private string interstitialAd = "video";
  private string rewardedVideoAd = "rewardedVideo";

  public bool isTargetPlayStore;
  public bool isTestAd;

  private void Start()
  {
      Advertisement.AddListener(this);
      InitializeAdvertisement();
  }

  private void InitializeAdvertisement()
  {

    if (Application.platform == RuntimePlatform.Android)
    {
      Advertisement.Initialize (playstoreID, true);
    }
    else if(Application.platform == RuntimePlatform.IPhonePlayer)
    {
      Advertisement.Initialize (appstoreID, true);
    }
  }

  public void PlayInterstitialAd()
  {

      if (!Advertisement.IsReady(interstitialAd)) return;
      Advertisement.Show(interstitialAd);
  }

  public void PlayRewardedVideoAd()
  {
      if (!Advertisement.IsReady(rewardedVideoAd)) return;
      Advertisement.Show(rewardedVideoAd);
  }

  void IUnityAdsListener.OnUnityAdsReady(string placementId)
  {
      //throw new System.NotImplementedException();
  }

  void IUnityAdsListener.OnUnityAdsDidError(string message)
  {
      //throw new System.NotImplementedException();
  }

  void IUnityAdsListener.OnUnityAdsDidStart(string placementId)
  {
      //throw new System.NotImplementedException();
  }

  void IUnityAdsListener.OnUnityAdsDidFinish(string placementId, ShowResult showResult)
  {

  }
}
