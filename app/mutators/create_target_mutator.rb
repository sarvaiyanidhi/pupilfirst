class CreateTargetMutator < ApplicationMutator
  include AuthorizeSchoolAdmin

  attr_accessor :title
  attr_accessor :target_group_id

  validates :title, presence: { message: 'TitleBlank' }
  validates :target_group_id, presence: { message: 'TargetGroupIdBlank' }

  def create_target
    target = Target.create!(title: title, target_group_id: target_group_id, role: 'founder', target_action_type: 'Todo', visibility: Target::VISIBILITY_DRAFT, safe_to_change_visibility: true)
    content_block = ContentBlock.create!(target: target, block_type: 'markdown', sort_index: 1, content: { markdown: content_block_text })
    { id: target.id, content_block_id: content_block.id, sample_content: content_block_text }
  end

  def content_block_text
    "# Target Content Builder\n\nThe following content types are supported:\n\n- Markdown Text\n- Image\n - Files\n - Embeds"
  end
end
