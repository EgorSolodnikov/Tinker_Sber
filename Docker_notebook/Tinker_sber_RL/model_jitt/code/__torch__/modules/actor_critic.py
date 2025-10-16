class MixedMlpBarlowTwinsActor(Module):
  __parameters__ = []
  __buffers__ = []
  training : bool
  _is_full_backward_hook : Optional[bool]
  mlp_encoder : __torch__.torch.nn.modules.container.Sequential
  actor : __torch__.modules.common_modules.MixedMlp
  obs_encoder : __torch__.torch.nn.modules.container.___torch_mangle_18.Sequential
  bn : __torch__.torch.nn.modules.batchnorm.BatchNorm1d
  def forward(self: __torch__.modules.actor_critic.MixedMlpBarlowTwinsActor,
    obs: Tensor,
    obs_hist: Tensor) -> Tensor:
    _0 = self.actor
    _1 = getattr(self.obs_encoder, "1")
    _2 = self.mlp_encoder
    _3 = torch.slice(obs_hist, 0, 0, 9223372036854775807)
    _4 = torch.slice(_3, 1, 1, 9223372036854775807)
    _5 = torch.slice(_4, 2, 0, 9223372036854775807)
    obs_hist_full = torch.cat([_5, torch.unsqueeze(obs, 1)], 1)
    b = ops.prim.NumToTensor(torch.size(obs_hist_full, 0))
    _6 = int(b)
    _7 = torch.slice(obs_hist_full, 0, 0, 9223372036854775807)
    _8 = torch.slice(_7, 1, 5, 9223372036854775807)
    _9 = torch.slice(_8, 2, 0, 9223372036854775807)
    input = torch.view(_9, [_6, -1])
    _10 = (_0).forward((_2).forward(_1, input, ), obs, )
    return _10
