module Intercom
  class FounderTaggingJob < ApplicationJob
    queue_as :default

    class << self
      attr_writer :mock

      def mock?
        defined?(@mock) ? @mock : Rails.env.test?
      end
    end

    def perform(founder, tag)
      return if self.class.mock?

      intercom = IntercomClient.new
      user = intercom.find_or_create_user(email: founder.email, name: founder.name)
      intercom.add_tag_to_user(user, tag)
    end
  end
end